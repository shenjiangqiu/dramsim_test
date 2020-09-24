#include <catch.hpp>
#include <fmt/format.h>
#include <iostream>
#include <dram_system.h>
#include <configuration.h>
#include <map>
TEST_CASE("ddr3test")
{
    std::map<int, int> map_to_gap;
    std::cout << "start ddr3 test" << std::endl;
    int cycle = 0;
    int last_cycle = 0;

    auto dummy_call_back = [&](uint64_t addr) {
        //std::cout << fmt::format("cycle:{} addr:{}", cycle, addr) << std::endl;
        map_to_gap[cycle - last_cycle]++;
        last_cycle = cycle;
    };

    dramsim3::Config config("configs/DDR3_4Gb_x8_1866.ini", ".");

    dramsim3::JedecDRAMSystem dramsys(config, ".", dummy_call_back,
                                      dummy_call_back);

    uint64_t addr = 0;
    for (int i = 0; i < 1000000; i++)
    {
        if (dramsys.WillAcceptTransaction(addr, false))
        {
            dramsys.AddTransaction(addr, false);
            addr += 64; //64 byte for the next access
        }
        dramsys.ClockTick();
        cycle++;
    }
    std::for_each(map_to_gap.begin(), map_to_gap.end(), [](auto &e) {
        std::cout << e.first << ": " << e.second << std::endl;
    });
    std::cout << "end ddr3 test" << std::endl;
}