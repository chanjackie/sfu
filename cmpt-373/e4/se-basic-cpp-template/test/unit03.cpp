#include "doctest.h"
#include "task03.h"


TEST_CASE("Empty list") {
  const std::vector<ex4::InfoBlob> blobs;

  std::vector<ex4::Action> result = task03(blobs);

  CHECK(result.empty());
}


TEST_CASE("No happy elements") {
  const std::vector<ex4::InfoBlob> blobs {
    { 0, 1.0, ex4::Emotion::SAD },
    { 0, 1.0, ex4::Emotion::SAD }
  };

  std::vector<ex4::Action> result = task03(blobs);

  CHECK(result.empty());
}


TEST_CASE("No sad elements") {
  const std::vector<ex4::InfoBlob> blobs {
    { 0, 1.0, ex4::Emotion::HAPPY },
    { 0, 1.0, ex4::Emotion::HAPPY }
  };

  std::vector<ex4::Action> result = task03(blobs);

  CHECK(result.empty());
}


TEST_CASE("Empty range") {
  const std::vector<ex4::InfoBlob> blobs {
    { 0, 1.0, ex4::Emotion::SAD },
    { 0, 1.0, ex4::Emotion::HAPPY }
  };

  std::vector<ex4::Action> result = task03(blobs);

  CHECK(result.empty());
}


TEST_CASE("Actionless emotions") {
  const std::vector<ex4::InfoBlob> blobs {
    { 3, 1.0, ex4::Emotion::HAPPY },
    { 3, 1.0, ex4::Emotion::PERPLEXED },
    { 0, 1.0, ex4::Emotion::SAD }
  };

  std::vector<ex4::Action> result = task03(blobs);

  const std::vector<ex4::Action> expected {
    ex4::Action::PLOT,
    ex4::Action::RUN
  };
  CHECK(expected == result);
}


TEST_CASE("Multiple actionless emotions") {
  const std::vector<ex4::InfoBlob> blobs {
    { 3, 1.0, ex4::Emotion::HAPPY },
    { 3, 1.0, ex4::Emotion::PERPLEXED },
    { 0, 1.0, ex4::Emotion::SAD },
    { 3, 1.0, ex4::Emotion::PERPLEXED }
  };

  std::vector<ex4::Action> result = task03(blobs);

  const std::vector<ex4::Action> expected {
    ex4::Action::PLOT,
    ex4::Action::RUN
  };
  CHECK(expected == result);
}


TEST_CASE("Normal functionality") {
  const std::vector<ex4::InfoBlob> blobs {
    {  3,  1.0, ex4::Emotion::HAPPY },
    {  0,  1.0, ex4::Emotion::HAPPY },
    {  0, -4.0, ex4::Emotion::SAD },
    { -2,  0.0, ex4::Emotion::SAD }
  };

  std::vector<ex4::Action> result = task03(blobs);

  const std::vector<ex4::Action> expected {
    ex4::Action::PLOT,
    ex4::Action::RUN,
    ex4::Action::PLOT,
    ex4::Action::RUN
  };
  CHECK(expected == result);
}

