#include <cstring>
#include "mesh.h"

#include "object.h"

bounce::Mesh::Mesh() {
    CreateVertexData();
    CreateColorData();
    CreateNormalData();
    CreateIndexData();
    
}

void bounce::Mesh::CreateIndexData() {
    GLuint* index_data = new GLuint[36] {
        0, 1, 2,
        0, 2, 3,
        3, 2, 6,
        3, 6, 7,
        6, 4, 7,
        6, 5, 4,
        4, 5, 1,
        4, 1, 0,
        5, 6, 2,
        5, 2, 1,
        0, 7, 4,
        0, 3, 7
    };
    
    
    index_data_ = index_data;
    index_count_ = 36;
}

void bounce::Mesh::CreateVertexData() {
    //GLfloat* vertex_data = new GLfloat[32]
    //{
    //    -1.0f, -1.0f, -1.0f,
    //    -1.0f, 1.0f, -1.0f,
    //     1.0f, 1.0f, -1.0f,
    //     1.0f, -1.0f, -1.0f,
    //    -1.0f, -1.0f, 1.0f,
    //    -1.0f, 1.0f,  1.0f,
    //     1.0f, 1.0f,  1.0f,
    //     1.0f, -1.0f, 1.0f,
    //};
    
    //vertex_data_ = vertex_data;
    //vertex_count_ = 32;
    
    GLfloat* vertex_data = new GLfloat[144] {
        -1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f,
        
        -1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f,
        
        1.0f, -1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f,
        
        1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 1.0f,
        
        1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, 1.0f,
        
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };
    
    vertex_data_ = vertex_data;
    vertex_count_ = 144;
}

void bounce::Mesh::CreateNormalData() {
    GLfloat* normal_data = new GLfloat[108];
    int i = 0;
    
    for (; i < 6; ++i) {
        normal_data[i * 3] = -1.0f;
        normal_data[i * 3 + 1] = 0.0f;
        normal_data[i * 3 + 2] = 0.0f;
    }
    
    for (; i < 12; ++i) {
        normal_data[i * 3] = 0.0f;
        normal_data[i * 3 + 1] = 0.0f;
        normal_data[i * 3 + 2] = -1.0f;
    }
    
    for (; i < 18; ++i) {
        normal_data[i * 3] = 1.0f;
        normal_data[i * 3 + 1] = 0.0f;
        normal_data[i * 3 + 2] = 0.0f;
    }
    
    for (; i < 24; ++i) {
        normal_data[i * 3] = 0.0f;
        normal_data[i * 3 + 1] = 0.0f;
        normal_data[i * 3 + 2] = 1.0f;
    }
    
    for (; i < 30; ++i) {
        normal_data[i * 3] = 0.0f;
        normal_data[i * 3 + 1] = -1.0f;
        normal_data[i * 3 + 2] = 0.0f;
    }
    
    for (; i < 36; ++i) {
        normal_data[i * 3] = 0.0f;
        normal_data[i * 3 + 1] = 1.0f;
        normal_data[i * 3 + 2] = 0.0f;
    }
    
    normal_data_ = normal_data;
    normal_count_ = 108;
}

void bounce::Mesh::CreateColorData()
{
    GLfloat* color_data = new GLfloat[12 * 3 * 3];
    
    int sides = 6;
    int verticesPerSide = 6;
    int colorsPerVertex = 3;
    int colorsPerSide = verticesPerSide * colorsPerVertex;
    
    for (int i = 0; i < sides; i++) {
        for (int j = 0; j < verticesPerSide; j++) {
            int index = i * colorsPerSide + j * colorsPerVertex;
            
            if (i == 1) {
                color_data[index] = 1.0f;
                color_data[index + 1] = 1.0f;
            }
            if (i % 2 == 0) {
                color_data[index] = 1.0f;
            }
            if (i % 3 == 0) {
                color_data[index + 1] = 1.0f;
            }
            if (i % 4 == 0 || i % 5 == 0) {
                color_data[index + 2] = 1.0f;
            }
            
            //			else {
            //				colorDataArray[index] = val;
            //				colorDataArray[index + 1] = val;
            //				colorDataArray[index + 2] = val;
            //			}
            
            //			std::cout << "i: " << i << " j: " << j << std::endl;
            //			std::cout << index << " ";
            //			std::cout << index + 1 << " ";
            //			std::cout << index + 2 << " ";
            //			std::cout << std::endl << std::endl;
            
        }
    }
    
    //	for (int i = 0; i < 108; i++) {
    //		std::cout << colorDataArray[i] << std::endl;
    //	}
    
    color_data_ = color_data;
    color_count_ = 108;
}