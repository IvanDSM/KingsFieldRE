#ifndef MODEL_H
#define MODEL_H

#include "datahandlers/kfmtdatahandler.h"
#include <QDataStream>
#include <QOpenGLBuffer>
#include <QVector3D>
#include <QVector4D>

/*!
 * \brief Class to represent a generic 3D model.
 * This class is made to accomodate the three kinds of model King's Field uses: MO, RTMD and TMD.
 * For MO files, each mesh in the animFrames vector represents a different frame of animation. The
 * baseMesh variable is used as the standard mesh storage for RTMD and TMD files and for the base
 * TMD mesh for MO files.
 */
class Model : public KFMTDataHandler
{
public:
    // Forward declarations for the internal structures

    /*!
     * \brief Structure for a XYZ vertex.
     */
    struct Vec3;

    /*!
     * \brief Structure for a TMD primitive.
     */
    struct Primitive;

    /*!
     * \brief Mesh structure for storing vertex arrays.
     */
    struct Mesh
    {
        std::vector<Vec3> vertices;
        std::vector<Vec3> normals;
        std::vector<Primitive> primitives;

        bool visible = true;

        Vec3& operator[](size_t vertex) { return vertices[vertex]; }
    };

    /*!
     * \brief Header for MIM/MO files.
     */
    struct MIMOrMOHeader
    {
        uint32_t animationCount;
        uint32_t tmdOffset;
        uint32_t morphTargetsOffset;
        uint32_t animationsOffset;
    };

    /*!
     * \brief Structure for a MO-style animation. Contains an array of frame indexes.
     */
    struct MOAnimation;

    /*!
     * \brief Structure for a MO-style frame.
     */
    struct MOFrame;

    /*!
     * \brief Structure for a decoded MO morph target packet.
     */
    struct MOPacket;

    explicit Model(KFMTFile& modelFile);
    void saveChanges() override {}

    std::vector<Mesh> baseObjects;
    float scale = 1.0f;

    std::vector<MOAnimation> animations;
    std::vector<MOFrame> animFrames;
    std::vector<Mesh> morphTargets;

private:
    void fixShiftedIndices();
    void loadMIM(const QByteArray& file);
    void loadMO(const QByteArray& file);
    void loadRTMD(const QByteArray& file);
    void loadTMD(const QByteArray& file);
    Model::MIMOrMOHeader readMIMOrMOHeader(QDataStream& stream);
};

/*!
 * \brief Operator for reading a primitive from a QDataStream.
 * \param in QDataStream to read from.
 * \param primitive Primitive to read into.
 * \return The QDataStream after reading.
 */
QDataStream& operator>>(QDataStream& in, Model::Primitive& primitive);

// Struct definitions

struct Model::MOAnimation
{
    std::vector<size_t> frameIndexes;
};

struct Model::MOFrame
{
    short Unknown00 = 0;
    short Weight = 0;
    short frameID = 0;
    std::vector<uint16_t> targets;

    MOFrame(short Unknown00_, short Weight_, short frameID_, short targetAmount)
        : Unknown00(Unknown00_), Weight(Weight_), frameID(frameID_)
    {
        targets.resize(targetAmount);
    }
};

struct Model::MOPacket
{
    short x = 0;
    short y = 0;
    short z = 0;

    MOPacket() = default;
    MOPacket(short x_, short y_, short z_) : x(x_), y(y_), z(z_) {}
    MOPacket(const MOPacket& other) : x(other.x), y(other.y), z(other.z) {}
};

struct Model::Primitive
{
    /*!
     * \brief Enum with terribly long names for the primitive flags.
     * Single/double faced only applies to polygon primitives.
     */
    enum class PrimitiveFlag;

    /*!
     * \brief Enum with terribly long names for the TMD primitive modes.
     */
    enum class PrimitiveMode;

    PrimitiveFlag flag;
    PrimitiveMode mode;
    uint8_t ilen;
    uint8_t olen;
    // The following variables represent packet elements. Not all of them are present in all types,
    // and the only reason all of them are declared here is to save time and not have to do some
    // sketchy inheritance stuff that'd make the file 5x bigger.
    uint8_t r0 = 255, g0 = 255, b0 = 255;
    uint8_t r1 = 255, g1 = 255, b1 = 255;
    uint8_t r2 = 255, g2 = 255, b2 = 255;
    uint8_t r3 = 255, g3 = 255, b3 = 255;
    uint8_t alpha = 255;

    uint8_t u0, v0;
    uint8_t u1, v1;
    uint8_t u2, v2;
    uint8_t u3, v3;

    uint16_t cba;
    uint16_t tsb;

    uint16_t vertex0, vertex1, vertex2, vertex3;
    uint16_t normal0, normal1, normal2, normal3;

    /*!
     * \brief Returns r0, g0 and b0 as a QVector4D
     * \return QVector4D with colour
     */
    QVector4D Colour0() const { return {r0 / 255.f, g0 / 255.f, b0 / 255.f, alpha / 255.f}; }
    QVector4D Colour1() const { return {r1 / 255.f, g1 / 255.f, b1 / 255.f, alpha / 255.f}; }
    QVector4D Colour2() const { return {r2 / 255.f, g2 / 255.f, b2 / 255.f, alpha / 255.f}; }
    QVector4D Colour3() const { return {r3 / 255.f, g3 / 255.f, b3 / 255.f, alpha / 255.f}; }

    std::vector<QVector2D> getAdaptedTexCoords() const;

    /*!
     * \brief Checks if a primitive is double sided.
     * \return Whether this is a double sided primitive.
     */
    bool isDoubleSided() const
    {
        auto flag_ = static_cast<uint8_t>(flag);
        return (flag_ >> 1) & 1;
    }

    /*!
     * \brief Checks whether this is a Gouraud shaded primitive.
     * \return Whether this is a Gouraud shaded primitive.
     */
    bool isGouraud() const { return ((static_cast<uint8_t>(mode) >> 5) & 1) == 1; }

    /*!
     * \brief Checks whether this is a gradation primitive.
     * \return Whether this is a gradation primitive.
     */
    bool isGradation() const { return static_cast<uint8_t>(flag) > 3; }

    /*!
     * \brief Checks whether this is a lit primitive.
     * \return Whether this is a lit primitive.
     */
    bool isLit() const { return (static_cast<uint8_t>(flag) & 1) == 0; }

    /*!
     * \brief Checks whether this is a quadrilateral primitive.
     * \return Whether this is a quadrilateral primitive.
     */
    bool isQuad() const
    {
        auto mode_ = static_cast<uint8_t>(mode);
        return (mode_ >> 5) && ((mode_ >> 3) & 1);
    }

    /*!
     * \brief Checks whether this primitive is flat shaded.
     * \return Whether this is a flat shade primitive.
     */
    bool isSmooth() const
    {
        auto mode_ = static_cast<uint8_t>(mode);
        return (mode_ >> 4) & 1;
    }

    /*!
     * \brief Checks whether this primitive is textured.
     * \return Whether this is a textured primitive.
     */
    bool isTextured() const
    {
        auto mode_ = static_cast<uint8_t>(mode);
        return (mode_ >> 2) & 1;
    }

    /*!
     * \brief Checks whether this is a triangle primitive.
     * \return Whether this is a triangle primitive.
     */
    bool isTriangle() const
    {
        auto mode_ = static_cast<uint8_t>(mode);
        return (mode_ >> 5) && !((mode_ >> 3) & 1);
    }

    void readFrom(QDataStream& stream);
    // Helper method for reading gradation
    void readGradation(QDataStream& stream)
    {
        if (isGradation())
        {
            stream >> r1;
            stream >> g1;
            stream >> b1;
            stream.skipRawData(1);
            stream >> r2;
            stream >> g2;
            stream >> b2;
            stream.skipRawData(1);
            if (isQuad())
            {
                stream >> r3;
                stream >> g3;
                stream >> b3;
                stream.skipRawData(1);
            }
        }
    }
    // Primitive packet readers
    void readx20(QDataStream& stream);
    void readx24(QDataStream& stream);
    void readx25(QDataStream& stream);
    void readx28(QDataStream& stream);
    void readx2c(QDataStream& stream);
    void readx30(QDataStream& stream);
    void readx34(QDataStream& stream);
    void readx38(QDataStream& stream);
    void readx3c(QDataStream& stream);
};

struct Model::Vec3
{
    float x;
    float y;
    float z;

    void applyPacket(const MOPacket& packet);
    void readSVECTOR(QDataStream& in);

    operator QVector3D() const { return {x, y, z}; }
};

// Enum definitions

enum class Model::Primitive::PrimitiveFlag
{
    SingleColorSingleFaceLightSourceNoCalc = 0b00000000, ///< 0x0
    SingleColorSingleFaceLightSourceCalc = 0b00000001,   ///< 0x1
    SingleColorDoubleFaceLightSourceNoCalc = 0b00000010, ///< 0x2
    SingleColorDoubleFaceLightSourceCalc = 0b00000011,   ///< 0x3
    GradationSingleFaceLightSourceNoCalc = 0b00000100,   ///< 0x4
    GradationSingleFaceLightSourceCalc = 0b00000101,     ///< 0x5
    GradationDoubleFaceLightSourceNoCalc = 0b00000110,   ///< 0x6
    GradationDoubleFaceLightSourceCalc = 0b00000111      ///< 0x7
};

enum class Model::Primitive::PrimitiveMode
{
    x20TriFlatNoTexOpaqueLit = 0b00100000,
    x21TriFlatNoTexOpaqueUnlit = 0b00100001,
    x22TriFlatNoTexTranslucentLit = 0b00100010,
    x23TriFlatNoTexTranslucentUnlit = 0b00100011,
    x24TriFlatTexOpaqueLit = 0b00100100,
    x25TriFlatTexOpaqueUnlit = 0b00100101,
    x26TriFlatTexTranslucentLit = 0b00100110,
    x27TriFlatTexTranslucentUnlit = 0b00100111,
    x28QuadFlatNoTexOpaqueLit = 0b00101000,
    x29QuadFlatNoTexOpaqueUnlit = 0b00101001,
    x2aQuadFlatNoTexTranslucentLit = 0b00101010,
    x2bQuadFlatNoTexTranslucentUnlit = 0b00101011,
    x2cQuadFlatTexOpaqueLit = 0b00101100,
    x2dQuadFlatTexOpaqueUnlit = 0b00101101,
    x2eQuadFlatTexTranslucentLit = 0b00101110,
    x2fQuadFlatTexTranslucentUnlit = 0b00101111,
    x30TriGouraudNoTexOpaqueLit = 0b00110000,
    x31TriGouraudNoTexOpaqueUnlit = 0b00110001,
    x32TriGouraudNoTexTranslucentLit = 0b00110010,
    x33TriGouraudNoTexTranslucentUnlit = 0b00110011,
    x34TriGouraudTexOpaqueLit = 0b00110100,
    x35TriGouraudTexOpaqueUnlit = 0b00110101,
    x36TriGouraudTexTranslucentLit = 0b00110110,
    x37TriGouraudTexTranslucentUnlit = 0b00110111,
    x38QuadGouraudNoTexOpaqueLit = 0b00111000,
    x39QuadGouraudNoTexOpaqueUnlit = 0b00111001,
    x3aQuadGouraudNoTexTranslucentLit = 0b00111010,
    x3bQuadGouraudNoTexTranslucentUnlit = 0b00111011,
    x3cQuadGouraudTexOpaqueLit = 0b00111100,
    x3dQuadGouraudTexOpaqueUnlit = 0b00111101,
    x3eQuadGouraudTexTranslucentLit = 0b00111110,
    x3fQuadGouraudTexTranslucentUnlit = 0b00111111,
    x40LineGradationOffOpaque = 0b01000000,
    x42LineGradationOffTranslucent = 0b01000010,
    x50LineGradationOnOpaque = 0b01010000,
    x52LineGradationOnTranslucent = 0b01010010,
    x64SpriteFreeOpaque = 0b01100100,
    x66SpriteFreeTranslucent = 0b01100110,
    x6cSprite1x1Opaque = 0b01101100,
    x6eSprite1x1Translucent = 0b01101110,
    x74Sprite8x8Opaque = 0b01110100,
    x76Sprite8x8Translucent = 0b01110110,
    x7cSprite16x16Opaque = 0b01111100,
    x7eSprite16x16Translucent = 0b01111110
};
#endif // MODEL_H
