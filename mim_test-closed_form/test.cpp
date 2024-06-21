#include "closedFormTest.h"

#include "gtest/gtest.h"

#include <algorithm> // for std::replace


extern "C" int calculate_iterations (float, float);
extern "C" void simulate (Data*, float);
extern "C" void simulate_n_seconds (Data*, float);
extern "C" void simulate_n_iterations (Data*, float, float);


static Data getStartingData (bool ownsMagnetsUpgrade, bool ownsFlywheel, bool ownsHamster)
{
  Data d = {0};
  d.maxEnergy = 1000.0f;
  d.speed = 20.0f;

  d.ownsMagnetsUpgrade = ownsMagnetsUpgrade;
  d.ownsFlywheel = ownsFlywheel;
  d.ownsHamster = ownsHamster;

  return d;
}

class mim_test : public testing::TestWithParam <std::tuple <float, float, bool, bool, bool>>
{
protected:

  mim_test ()
    : FPS (std::get <0> (GetParam ()))
    , elapsed_seconds (std::get <1> (GetParam ()))
    , ownsMagnetsUpgrade (std::get <2> (GetParam ()))
    , ownsFlywheel (std::get <3> (GetParam ()))
    , ownsHamster (std::get <4> (GetParam ()))
  {
    expected = getStartingData (ownsMagnetsUpgrade, ownsFlywheel, ownsHamster);

    int const iterations = calculate_iterations (elapsed_seconds, FPS);
    for (int i = 0; i < iterations; ++i)
    {
      simulate (&expected, FPS);
    }
  }


protected:
  Data expected = {};
  float const FPS;
  float const elapsed_seconds;
  bool const ownsMagnetsUpgrade;
  bool const ownsFlywheel;
  bool const ownsHamster;


  float const EPSILON = 0.1f; // margin of error to account for accumulated fp truncations

};


TEST_P (mim_test, simulate_n_seconds)
{
  Data actual = getStartingData (ownsMagnetsUpgrade, ownsFlywheel, ownsHamster);

  simulate_n_seconds (&actual, elapsed_seconds);

  EXPECT_NEAR (actual.speed, expected.speed, EPSILON);
  EXPECT_NEAR (actual.storedEnergy, expected.storedEnergy, EPSILON);
}

//TEST_P (mim_test, simulate_n_iterations)
//{
//  Data actual = getStartingData (ownsMagnetsUpgrade, ownsFlywheel, ownsHamster);
//
//  simulate_n_iterations (&actual, elapsed_seconds, FPS);
//
//  EXPECT_NEAR (actual.speed, expected.speed, EPSILON);
//  EXPECT_NEAR (actual.storedEnergy, expected.storedEnergy, EPSILON);
//}


// pick one
auto FPS_values = testing::Values (30.0f);
//auto FPS_values = testing::Values (10.0f, 30.0f, 50.0f);

float const HOUR = 60.0f * 60.f;
float const DAY = HOUR * 24.f;
// pick one - start, end, increment
auto elapsed_seconds_values = testing::Range (5.f, HOUR, 60.f * 2.f);
//auto elapsed_seconds_values = testing::Range (1.f * HOUR, 8.f * HOUR, HOUR);
//auto elapsed_seconds_values = testing::Range (4.f * DAY, 8.f * DAY, DAY);

INSTANTIATE_TEST_SUITE_P (MyGroup, mim_test, testing::Combine (
      FPS_values             // FPS
    , elapsed_seconds_values // elapsed_seconds
    , testing::Bool ()       // ownsMagnetsUpgrade -> true, false
    , testing::Bool ()       // ownsFlywheel       -> true, false
    , testing::Bool ()       // ownsHamster        -> true, false
  ),
  [] (testing::TestParamInfo <mim_test::ParamType> const& info)
  {
    // convert test parameter data into test name
    std::string name = std::string ("FPS") + std::to_string (std::get <0> (info.param));
    name += std::string ("_time") + std::to_string (std::get <1> (info.param));
    name += std::get <2> (info.param) ? "_ownsMagnet" : "";
    name += std::get <3> (info.param) ? "_ownsFlywheel" : "";
    name += std::get <4> (info.param) ? "_ownsHamster" : "";
    std::replace (name.begin (), name.end (), '.', '_');
    return name;
  });
