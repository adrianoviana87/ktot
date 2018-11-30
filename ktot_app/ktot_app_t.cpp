#include <chrono>
#include <ratio>
#include <ctime>
#include <iomanip>
#include <filesystem>

#include "ktot_app_t.h"
#include "ktot/crosscutting/serialization.h"

template <typename Clock, typename Duration>
std::ostream &operator<<(std::ostream &stream,
                         const std::chrono::time_point<Clock, Duration> &time_point)
{
    const time_t time = Clock::to_time_t(time_point);
#if __GNUC__ > 4 || \
    ((__GNUC__ == 4) && __GNUC_MINOR__ > 8 && __GNUC_REVISION__ > 1)
    // Maybe the put_time will be implemented later?
    struct tm tm;
    localtime_r(&time, &tm);
    return stream << std::put_time(&tm, "%c"); // Print standard date&time
#else
    char buffer[26];
    ctime_r(&time, buffer);
    buffer[24] = '\0'; // Removes the newline that is added
    return stream << buffer;
#endif
}

namespace ktot
{
ktot_app_t::ktot_app_t(
    std::ostream &output,
    app_settings_ptr settings,
    task_service_ptr task_service)
    : m_output(output),
      m_settings(settings),
      m_task_service(std::move(task_service))
{
}

void ktot_app_t::init()
{
    std::filesystem::create_directories(m_settings->tasks_path);
}

void ktot_app_t::save_settings()
{
    serialize(*m_settings);
}

void ktot_app_t::list_tasks()
{
    auto tasks = m_task_service->list();
    for (auto &task : tasks)
    {
        print(*task);
    }
}

void ktot_app_t::print(const task_t &task)
{
    m_output << "Task (" << task.id() << "): " << task.name() << std::endl;
    m_output << "Works:" << std::endl;
    auto now = std::chrono::system_clock::now();
    for (auto &work : task.works())
    {
        m_output << "Started at: " << work->startedAt() << std::endl;
        if (!work->endedAt())
        {
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - work->startedAt());
            auto fraction = duration.count() / (60.0 * 60.0);
            m_output << "WORKING FOR " << fraction << " (fractions of an hour)" << std::endl;
        }
        else
        {
            m_output << "Ended at: " << *work->endedAt() << std::endl;
            auto duration = std::chrono::duration_cast<std::chrono::seconds>((*work->endedAt()) - work->startedAt());
            auto fraction = duration.count() / (60.0 * 60.0);
            m_output <<  "Duration: " << fraction << " (fractions of an hour)" << std::endl;
        }
    }
}

void ktot_app_t::start_task_by_name(const std::string &name)
{
    auto task = m_task_service->start_by_name(name);
    m_task_service->save(task);
    print(*task);
}

app_settings_ptr ktot_app_t::settings() const
{
    return m_settings;
}

void ktot_app_t::end_all_tasks()
{
    m_task_service->end_all();
}

void ktot_app_t::print_current_task()
{
    auto tasks = m_task_service->list();
    for (auto &task : tasks)
    {
        if (task->is_incomplete())
        {
            print(*task);
        }
    }
}
} // namespace ktot