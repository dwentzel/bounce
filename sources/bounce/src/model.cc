#include "model.h"

void bounce::Model::AddMeshStartIndex(int index)
{
    mesh_start_indices_.push_back(index);
}

void bounce::Model::AddMeshSize(int size)
{
    mesh_sizes_.push_back(size);
}

void bounce::Model::AddMeshMaterialIndex(int index)
{
    material_indices_.push_back(index);
}