#ifndef MODEL_H
#define MODEL_H

#include "kfmterror.h"
#include "kftypes.h"
#include "tfile.h"


/*!
 * \brief Class to represent a generic 3D model.
 * This class is made to accomodate the three kinds of model King's Field uses: MO, RTMD and TMD.
 * For MO files, each mesh in the animFrames vector represents a different frame of animation. The
 * baseMesh variable is used as the standard mesh storage for RTMD and TMD files and for the base
 * TMD mesh for MO files.
 */
class Model
{
public:
    // Internal enums and structures
    
    /*!
     * \brief Structure for a XYZ vertex.
     */
    struct Vec3
    {
        float x;
        float y;
        float z;
        
        void readSVECTOR(QDataStream &in);
    };
    
    /*!
     * \brief Structure for a MO-style animation. Contains an array of frame indexes.
     */
    struct Animation
    {
        std::vector<size_t> frameIndexes;
    };
    
    /*!
     * \brief Structure for a TMD primitive.
     */
    struct Primitive
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
        uint8_t r0, g0, b0;
        uint8_t r1, g1, b1;
        uint8_t r2, g2, b2;
    
        uint8_t u0, v0;
        uint8_t u1, v1;
        uint8_t u2, v2;
    
        uint16_t cba;
        uint16_t tsb;
    
        uint16_t vertex0, vertex1, vertex2, vertex3;
        uint16_t normal0, normal1, normal2, normal3;
        
        /*!
         * \brief Checks whether a primitive's flag indicates it is a gradation primitive.
         * \param flag Primitive flag
         * \return Whether the primitive is a gradation primitive.
         */
        static bool isGradation(PrimitiveFlag flag) { return static_cast<uint8_t>(flag) > 3; }
        /*!
         * \brief Checks whether a primitive's flag indicates it is a single color primitive.
         * \param flag Primitive flag
         * \return Whether the primitive is a single color primitive.
         */
        static bool isSingleColor(PrimitiveFlag flag) { return static_cast<uint8_t>(flag) < 4; }
    };
    
    /*!
     * \brief Mesh structure for storing vertex arrays.
     */
    struct Mesh
    {
        std::vector<Vec3> vertices;
        
        Vec3 &operator[](size_t vertex) {return vertices[vertex];}
    };
    
    explicit Model(TFile &tFile, unsigned int fileIndex);
    
    Mesh baseMesh;
    std::vector<Vec3> normals;
    std::vector<Primitive> primitives;
    float scale;
    
    std::vector<Animation> animations;
    std::vector<Mesh> animFrames;
    
private:
    void loadMO(const QByteArray &file);
    void loadRTMD(const QByteArray &file);
    void loadTMD(const QByteArray &file);
};

/*!
 * \brief Operator for reading a primitive from a QDataStream
 * \param in QDataStream to read from
 * \param primitive Primitive to read into
 * \return The QDataStream after reading
 */
QDataStream &operator>>(QDataStream &in, Model::Primitive& primitive);

// Enum definitions

enum class Model::Primitive::PrimitiveFlag
{
    SingleColorSingleFaceLightSourceNoCalc = 0b00000000, ///< 0x0
    SingleColorSingleFaceLightSourceCalc = 0b00000001, ///< 0x1
    SingleColorDoubleFaceLightSourceNoCalc = 0b00000010, ///< 0x2
    SingleColorDoubleFaceLightSourceCalc = 0b00000011, ///< 0x3
    GradationSingleFaceLightSourceNoCalc = 0b00000100, ///< 0x4
    GradationSingleFaceLightSourceCalc = 0b00000101, ///< 0x5
    GradationDoubleFaceLightSourceNoCalc = 0b00000110, ///< 0x6
    GradationDoubleFaceLightSourceCalc = 0b00000111 ///< 0x7
};

enum class Model::Primitive::PrimitiveMode
{
    TriFlatNoTexOpaqueLit = 0b00100000, ///< 0x20
    TriFlatNoTexOpaqueUnlit = 0b00100001, ///< 0x21
    TriFlatNoTexTranslucentLit = 0b00100010, ///< 0x22
    TriFlatNoTexTranslucentUnlit = 0b00100011, ///< 0x23
    TriFlatTexOpaqueLit = 0b00100100, ///< 0x24
    TriFlatTexOpaqueUnlit = 0b00100101, ///< 0x25
    TriFlatTexTranslucentLit = 0b00100110, ///< 0x26
    TriFlatTexTranslucentUnlit = 0b00100111, ///< 0x27
    TriGouraudNoTexOpaqueLit = 0b00110000, ///< 0x30
    TriGouraudNoTexOpaqueUnlit = 0b00110001, ///< 0x31
    TriGouraudNoTexTranslucentLit = 0b00110010, ///< 0x32
    TriGouraudNoTexTranslucentUnlit = 0b00110011, ///< 0x33
    TriGouraudTexOpaqueLit = 0b00110100, ///< 0x34
    TriGouraudTexOpaqueUnlit = 0b00110101, ///< 0x35
    TriGouraudTexTranslucentLit = 0b00110110, ///< 0x36
    TriGouraudTexTranslucentUnlit = 0b00110111, ///< 0x37
    QuadFlatNoTexOpaqueLit = 0b00101000, ///< 0x28
    QuadFlatNoTexOpaqueUnlit = 0b00101001, ///< 0x29
    QuadFlatNoTexTranslucentLit = 0b00101010, ///< 0x2a
    QuadFlatNoTexTranslucentUnlit = 0b00101011, ///< 0x2b
    QuadFlatTexOpaqueLit = 0b00101100, ///< 0x2c
    QuadFlatTexOpaqueUnlit = 0b00101101, ///< 0x2d
    QuadFlatTexTranslucentLit = 0b00101110, ///< 0x2e
    QuadFlatTexTranslucentUnlit = 0b00101111, ///< 0x2f
    QuadGouraudNoTexOpaqueLit = 0b00111000, ///< 0x38
    QuadGouraudNoTexOpaqueUnlit = 0b00111001, ///< 0x39
    QuadGouraudNoTexTranslucentLit = 0b00111010, ///< 0x3a
    QuadGouraudNoTexTranslucentUnlit = 0b00111011, ///< 0x3b
    QuadGouraudTexOpaqueLit = 0b00111100, ///< 0x3c
    QuadGouraudTexOpaqueUnlit = 0b00111101, ///< 0x3d
    QuadGouraudTexTranslucentLit = 0b00111110, ///< 0x3e
    QuadGouraudTexTranslucentUnlit = 0b00111111, ///< 0x3f
    LineGradationOffOpaque = 0b01000000, ///< 0x40
    LineGradationOffTranslucent = 0b01000010, ///< 0x42
    LineGradationOnOpaque = 0b01010000, ///< 0x50
    LineGradationOnTranslucent = 0b01010010, ///< 0x52
    SpriteFreeOpaque = 0b01100100, ///< 0x64
    SpriteFreeTranslucent = 0b01100110, ///< 0x66
    Sprite1x1Opaque = 0b01101100, ///< 0x6c
    Sprite1x1Translucent = 0b01101110, ///< 0x6e
    Sprite8x8Opaque = 0b01110100, ///< 0x74
    Sprite8x8Translucent = 0b01110110, ///< 0x76
    Sprite16x16Opaque = 0b01111100, ///< 0x7c
    Sprite16x16Translucent = 0b01111110 ///< 0x7e
};

#endif // MODEL_H
