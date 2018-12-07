#include "ktot/domain/task_t.h"
#include <algorithm>
#include <chrono>
#include <string>
#include "ktot/crosscutting/time_utils.h"

using namespace std::chrono_literals;
namespace ktot {
task_t::task_t(std::string name) : m_name(name) {}

const std::string &task_t::name() const { return m_name; }

void task_t::name(std::string val) { m_name = val; }

const std::string &task_t::external_id() const { return m_externalId; }

void task_t::external_id(std::string val) { m_externalId = val; }

const std::string &task_t::id() const { return m_id; }

void task_t::id(std::string val) { m_id = val; }

const std::vector<work_ptr> &ktot::task_t::works() const { return m_works; }

void task_t::works(std::vector<ktot::work_ptr> val) { m_works = val; }

bool task_t::terminate() {
  auto works = incomplete_works();
  auto any_incomplete = works.size() > 0;
  if (any_incomplete) {
    for (auto &work : works) {
      work->endedAt(std::chrono::system_clock::now());
    }
  }

  return any_incomplete;
}

bool task_t::finish_incomplete() {
  auto works = incomplete_works();
  auto any_incomplete = works.size() > 0;
  if (any_incomplete) {
    for (auto &work : works) {
      work->endedAt(work->startedAt());
    }
  }

  return any_incomplete;
}

work_ptr task_t::start() {
  finish_incomplete();
  auto work = std::make_shared<work_t>(std::chrono::system_clock::now());
  m_works.push_back(work);
  return work;
}

bool task_t::is_incomplete() const { return incomplete_works().size() > 0; }

std::vector<work_ptr> task_t::incomplete_works() const {
  std::vector<work_ptr> works{};
  for (auto &work : m_works) {
    if (!work->endedAt()) {
      works.push_back(work);
    }
  }

  return works;
}

std::chrono::seconds task_t::total_works() const {
  std::chrono::duration dur_secs = 0s;
  for (auto &work : m_works) {
    dur_secs += work->duration();
  }

  return dur_secs;
}

std::chrono::seconds task_t::total_works_in_date(
    work_t::time_point time_point) const {
  std::chrono::duration dur_secs = 0s;
  for (auto &work : m_works) {
    if (is_in_date(time_point, work->startedAt())) {
      dur_secs += work->duration();
    }
  }

  return dur_secs;
}

std::chrono::seconds task_t::total_works_today() const {
  std::chrono::duration dur_secs = 0s;
  auto now = work_t::time_point::clock::now();
  for (auto &work : m_works) {
    if (is_in_date(now, work->startedAt())) {
      dur_secs += work->duration();
    }
  }

  return dur_secs;
}

}  // namespace ktot