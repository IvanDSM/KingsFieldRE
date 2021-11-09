#ifndef TMDREADER_H
#define TMDREADER_H

#include "model.h"
#include "utilities.h"

class TMDReader
{
public:
    TMDReader(Model& model_) : model(model_) {}
    void read(const QByteArray& tmd);

private:
    // Structs

    /*!
     * \brief Structure for a TMD object table entry.
     */
    struct TMDObject
    {
        uint32_t vertexOffset;
        uint32_t vertexCount;
        uint32_t normalOffset;
        uint32_t normalCount;
        uint32_t primitiveOffset;
        uint32_t primitiveCount;
        int32_t scale;
    };

private:
    bool isShadowTower = false;
    Model& model;
    Model::Mesh* curMesh;
    TMDObject* objectTable;

    // FIXME: I'm really unhappy with this.
    // Ideally we'd just index into TMDObjects in the table, but we need to
    // keep track of the SVECTOR we're reading without having to recalculate it
    // every time, as well as have the position of the current primitive.
    // I thought of reading the object table into a special class but I'm not
    // fond of the idea of doing unnecessary copies like that.
    // There has to be a better way to do this.
    const Model::SVECTOR* curVertexPtr;
    size_t curVertexCount;
    const Model::SVECTOR* curNormalPtr;
    size_t curNormalCount;
    const uint8_t* curPrimPtr;
    size_t curPrimitiveCount;

    // Primitive stuff
    inline auto& curPrimFlag() { return curPrimPtr[2]; }
    inline auto& curPrimMode() { return curPrimPtr[3]; }

    /*!
     * \brief Checks if the current primitive is double sided.
     * \return Whether it is a double sided primitive.
     */
    static bool isDoubleSided(uint8_t flag) { return (flag >> 1) & 1; }

    /*!
     * \brief Checks if the current primitive is Gouraud shaded.
     * \return Whether it is a Gouraud shaded primitive.
     */
    static bool isGouraud(uint8_t mode) { return ((mode >> 4) & 1) == 1; }

    /*!
     * \brief Checks if the current primitive is a gradation primitive.
     * \return Whether it is a gradation primitive.
     */
    static bool isGradation(uint8_t flag) { return flag > 3; }

    /*!
     * \brief Checks if the current primitive is a quad.
     * \return Whether it is a quad primitive.
     */
    static bool isQuad(uint8_t mode) { return (mode >> 5) && ((mode >> 3) & 1); }

    /*!
     * \brief Checks if the current primitive is textured.
     * \return Whether it is a textured primitive.
     */
    static bool isTextured(uint8_t mode) { return (mode >> 2) & 1; }

    /*!
     * \brief Reads a TMD primitive. To force a specific primitive, pass its mode as an argument.
     * \param manualPrimMode Optional argument for primitive mode. Only use to force a specific primitive!
     */
    void readPrimitive(uint8_t manualPrimMode = 0);
    // readPrimitive subroutines
    void readColors(float alpha, size_t offset);
    void readPositionsAndNormals();
    void readTexcoords();
    // Primitive packet readers
    void readx20(float alpha);
    void readx24(float alpha);
    void readx25(float alpha);
    void readx28(float alpha);
    void readx2c(float alpha);
    void readx30(float alpha);
    void readx34(float alpha);
    void readx38(float alpha);
    void readx3c(float alpha);
};

#endif // TMDREADER_H
