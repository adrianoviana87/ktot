#pragma once
#include <ostream>
#include <memory>
#include "ktot/domain/task_service_t.h"
#include "ktot/crosscutting/app_settings_t.h"


namespace ktot
{
    class ktot_app_t
    {
    public:
        ktot_app_t(
            std::ostream& output,
            app_settings_ptr settings,
            task_service_ptr task_service);

        void list_tasks();
        void save_settings();
        void init();
        void start_task_by_name(const std::string& name);
        void end_all_tasks();
        void print_current_task();
        app_settings_ptr settings() const;
    private:
        void print(const task_t& task);
        task_service_ptr m_task_service;
        app_settings_ptr m_settings;
        std::ostream& m_output;

    };
}