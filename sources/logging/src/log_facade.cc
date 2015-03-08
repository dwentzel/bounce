#include "log_facade.h"
#include "default_log_manager.h"

#include "framework/contracts.h"

std::unique_ptr<bounce::LogManagerFactoryBase>bounce::LogFacade::factory_;
std::unique_ptr<bounce::LogManager>bounce::LogFacade::log_manager_;


//void bounce::LogManager::SetImplementation(std::unique_ptr<LogManagerImpl> implementation)
//{
//    impl_ = std::move(implementation);
//}

void bounce::LogFacade::Startup()
{
    CONTRACT_ENSURES(log_manager_ != nullptr);
    
    if (factory_ == nullptr) {
        factory_ = std::unique_ptr<LogManagerFactoryBase>(new LogManagerFactory<DefaultLogManager>());
    }
    
    log_manager_ = std::move(factory_->Create());
    
    log_manager_->Startup();
}

void bounce::LogFacade::Shutdown()
{
    CONTRACT_REQUIRES(log_manager_ != nullptr);
    log_manager_->Shutdown();
}

std::wostream& bounce::LogFacade::Log(const LogLevel& log_level)
{
    CONTRACT_REQUIRES(log_manager_ != nullptr);
    return log_manager_->Log(log_level);
}

void bounce::LogFacade::AddOutput(std::unique_ptr<LogOutput> output)
{
    CONTRACT_REQUIRES(log_manager_ != nullptr);
    CONTRACT_REQUIRES(output != nullptr);
    log_manager_->AddOutput(std::move(output));
}
