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
    // Internal structures
    
    /*!
     * \brief Structure for a XYZ vertex.
     */
    struct Vec3
    {
        float x;
        float y;
        float z;
    };
    
    /*!
     * \brief Structure for a MO-style animation. Contains an array of frame indexes.
     */
    struct Animation
    {
        std::vector<size_t> frameIndexes;
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
    
    std::vector<Animation> animations;
    std::vector<Mesh> animFrames;
    
private:
    
    void loadMO(const QByteArray &file);
    void loadRTMD(const QByteArray &file);
    void loadTMD(const QByteArray &file);
};

#endif // MODEL_H
