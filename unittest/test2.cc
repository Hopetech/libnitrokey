#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()
#include "catch.hpp"

#include <iostream>
#include <string.h>
#include <NitrokeyManager.h>
#include "device_proto.h"
#include "log.h"
//#include "stick10_commands.h"
#include "stick20_commands.h"

using namespace std;
using namespace nitrokey::device;
using namespace nitrokey::proto::stick20;
using namespace nitrokey::log;
using namespace nitrokey::misc;


TEST_CASE("test", "[test]") {
  Stick20 stick;
  bool connected = stick.connect();
  REQUIRE(connected == true);

  Log::instance().set_loglevel(Loglevel::DEBUG_L2);

  {
    auto p = get_payload<EnableEncryptedPartition>();
    p.set_kind_user();
    strcpyT(p.password, "123456");
    EnableEncryptedPartition::CommandTransaction::run(stick, p);
  }
 {
    auto p = get_payload<DisableEncryptedPartition>();
    p.set_kind_user();
    strcpyT(p.password, "123456");
    DisableEncryptedPartition::CommandTransaction::run(stick, p);
  }

  stick.disconnect();
}
