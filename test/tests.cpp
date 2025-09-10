#include <catch2/catch_test_macros.hpp>
#include <libsdb/Process.hpp>
#include <sys/types.h>
#include <signal.h>
#include <libsdb/Error.hpp>

using namespace sdb;

namespace{
    bool process_exists(pid_t pid){
        // no signal is sent, but existence and permission checks are still performed; 
        // this can be used to check for the existence of a process ID or process group ID that the caller is permitted to signal.
        auto ret = kill(pid, 0);
        return ret !=-1 && errno != ESRCH;
    }
}

TEST_CASE("Porcess::launch success", "[Process]") {
    auto proc = Process::launch("yes");
    REQUIRE(process_exists(proc->pid()));
}

TEST_CASE("Process::launch no such program", "[Process]") {
    REQUIRE_THROWS_AS(Process::launch("you_do_not_have_to_be_good"), Error);
}