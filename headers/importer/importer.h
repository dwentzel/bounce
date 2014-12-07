#ifndef BOUNCE_IMPORTER_IMPORTER_H_
#define BOUNCE_IMPORTER_IMPORTER_H_

#include <string>

#include "framework/resource_loader.h"
#include "imported_model.h"

namespace bounce {
        
    class Importer {
    private:
        const ResourceLoader& resource_loader_;

        Importer(const Importer&) = delete;
        Importer& operator=(const Importer&) = delete;

    public:
        Importer(const ResourceLoader& resource_loader);
                
        ImportedModel LoadModel(const std::string& filename) const;
    };    
}

#endif // BOUNCE_IMPORTER_IMPORTER_H_