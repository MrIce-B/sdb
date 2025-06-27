#include <catch2/catch_test_macros.hpp>
#include <libsdb/Process.hpp>

using namespace sdb;

namespace{
    bool process_exists(pid_t pid);
}

TEST_CASE("Porcess::launch success", "[Process]") {
    auto proc = Process::launch("yes");
    REQUIRE(process_exists(proc->pid()));
}