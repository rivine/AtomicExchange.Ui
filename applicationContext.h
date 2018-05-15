#include <QQmlApplicationEngine>

class ApplicationContext
{
    
    ApplicationContext() {}
    
    QQmlApplicationEngine* engine;
       
    public:
    
        ApplicationContext(ApplicationContext const&) = delete;
        void operator=(ApplicationContext const&)  = delete;
        static ApplicationContext& Instance()
        {
            static ApplicationContext    instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return instance;
        }
        
        void setEngine(QQmlApplicationEngine* engine){
         this->engine = engine;
        }
        QQmlApplicationEngine* getEngine(){
            return this->engine;
        }
};