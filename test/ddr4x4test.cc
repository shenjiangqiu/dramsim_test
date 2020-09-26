#include <iostream>
#include <dram_system.h>
#include <configuration.h>
#include <fmt/format.h>

#include <catch.hpp>
#include <map>
#include <algorithm>
TEST_CASE("test_ddr4x4")
{
    std::cout << "start ddr4x4 test" << std::endl;
    int cycle;
    std::map<int, int> map_to_gap;
    int last_cycle = 0;
    auto dummy_call_back = [&](uint64_t addr) {
        map_to_gap[cycle - last_cycle]++;
        //std::cout << fmt::format("cycle:{} addr:{}", cycle, addr) << std::endl;
        last_cycle = cycle;
    };

    dramsim3::Config config("configs/DDR4_4Gb_x4_2666.ini", ".");

    dramsim3::JedecDRAMSystem dramsys(config, ".", dummy_call_back,
                                      dummy_call_back);

    uint64_t addr = 0;
    for (int i = 0; i < 10000000; i++)
    {
        if (dramsys.WillAcceptTransaction(addr, false))
        {
            dramsys.AddTransaction(addr, false);
            addr = addr + 64;
            addr = addr % (1 << 10);
        }
        dramsys.ClockTick();
        cycle++;
    }
    std::for_each(map_to_gap.begin(), map_to_gap.end(), [](auto &e) {
        std::cout << e.first << ": " << e.second << std::endl;
    });
    std::cout << "end ddr4x4 test" << std::endl;
}