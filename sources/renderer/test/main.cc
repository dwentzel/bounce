#include "contrib/disable_clang_warnings.h"
#include "gtest/gtest.h"
#include "contrib/enable_clang_warnings.h"

#include "logging/log_manager.h"

class Environment : public ::testing::Environment {
    // Override this to define how to set up the environment.
    virtual void SetUp()
    {
        bounce::LogManager::SetFactory(std::unique_ptr<bounce::LogManagerImplementationFactoryBase>(new bounce::LogManagerImplementationFactory<bounce::NullLogManagerImpl>()));
    }
    // Override this to define how to tear down the environment.
    virtual void TearDown() {}
};


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new Environment());
    return RUN_ALL_TESTS();
}
