#include <Configuration.h>
#include "gtest/gtest.h"

using namespace javaish;

TEST(ConfigurationTest, BasicConfigTest){
	Configuration config;
	EXPECT_TRUE(config.read("./test/test.config"));
	std::string value = config.getValue("SAMPLE.TEST.KEY");
	EXPECT_TRUE(strcmp("VALUE", value.c_str()) == 0);

	Configuration failConfig;
	EXPECT_FALSE(failConfig.read("./test.config"));
}

