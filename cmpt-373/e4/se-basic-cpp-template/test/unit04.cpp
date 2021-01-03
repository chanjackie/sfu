#include "doctest.h"
#include "task04.h"


TEST_CASE("Empty list") {
  std::vector<ex4::InfoBlob> blobs;

  task04(blobs);

  CHECK(blobs.empty());
}


TEST_CASE("No happy or perplexed elements") {
  const std::vector<ex4::InfoBlob> expected {
    { 0, 1.0, ex4::Emotion::SAD },
    { 1, 2.0, ex4::Emotion::SAD }
  };
  std::vector<ex4::InfoBlob> blobs = expected;

  task04(blobs);

  CHECK(expected == blobs);
}


TEST_CASE("No happy elements") {
  const std::vector<ex4::InfoBlob> expected {
    { 0, 1.0, ex4::Emotion::SAD },
    { 1, 2.0, ex4::Emotion::PERPLEXED },
    { 2, 3.0, ex4::Emotion::SAD }
  };
  std::vector<ex4::InfoBlob> blobs = expected;

  task04(blobs);

  CHECK(expected == blobs);
}


TEST_CASE("No perplexed elements") {
  std::vector<ex4::InfoBlob> blobs {
    { 0, 2.0, ex4::Emotion::SAD },
    { 1, 1.0, ex4::Emotion::HAPPY },
    { 2, 2.0, ex4::Emotion::SAD },
    { 3, 3.0, ex4::Emotion::HAPPY },
    { 4, 2.0, ex4::Emotion::SAD }
  };

  task04(blobs);

  const std::vector<ex4::InfoBlob> expected {
    { 0, 2.0, ex4::Emotion::SAD },
    { 2, 2.0, ex4::Emotion::SAD },
    { 4, 2.0, ex4::Emotion::SAD },
    { 1, 1.0, ex4::Emotion::HAPPY },
    { 3, 3.0, ex4::Emotion::HAPPY }
  };

  CHECK(expected == blobs);
}


TEST_CASE("Perplexed at the beginning") {
  std::vector<ex4::InfoBlob> blobs {
    { 0, 2.0, ex4::Emotion::PERPLEXED },
    { 1, 1.0, ex4::Emotion::HAPPY },
    { 2, 2.0, ex4::Emotion::SAD },
    { 3, 3.0, ex4::Emotion::HAPPY },
    { 4, 2.0, ex4::Emotion::SAD }
  };

  task04(blobs);

  const std::vector<ex4::InfoBlob> expected {
    { 1, 1.0, ex4::Emotion::HAPPY },
    { 3, 3.0, ex4::Emotion::HAPPY },
    { 0, 2.0, ex4::Emotion::PERPLEXED },
    { 2, 2.0, ex4::Emotion::SAD },
    { 4, 2.0, ex4::Emotion::SAD }
  };

  CHECK(expected == blobs);
}


TEST_CASE("Perplexed in the middle") {
  std::vector<ex4::InfoBlob> blobs {
    { 0, 2.0, ex4::Emotion::SAD },
    { 1, 1.0, ex4::Emotion::HAPPY },
    { 2, 2.0, ex4::Emotion::PERPLEXED },
    { 3, 3.0, ex4::Emotion::HAPPY },
    { 4, 2.0, ex4::Emotion::SAD }
  };

  task04(blobs);

  const std::vector<ex4::InfoBlob> expected {
    { 0, 2.0, ex4::Emotion::SAD },
    { 1, 1.0, ex4::Emotion::HAPPY },
    { 3, 3.0, ex4::Emotion::HAPPY },
    { 2, 2.0, ex4::Emotion::PERPLEXED },
    { 4, 2.0, ex4::Emotion::SAD }
  };

  CHECK(expected == blobs);
}


TEST_CASE("Perplexed at the end") {
  std::vector<ex4::InfoBlob> blobs {
    { 0, 2.0, ex4::Emotion::SAD },
    { 1, 1.0, ex4::Emotion::HAPPY },
    { 2, 2.0, ex4::Emotion::SAD },
    { 3, 3.0, ex4::Emotion::HAPPY },
    { 4, 2.0, ex4::Emotion::PERPLEXED }
  };

  task04(blobs);

  const std::vector<ex4::InfoBlob> expected {
    { 0, 2.0, ex4::Emotion::SAD },
    { 2, 2.0, ex4::Emotion::SAD },
    { 1, 1.0, ex4::Emotion::HAPPY },
    { 3, 3.0, ex4::Emotion::HAPPY },
    { 4, 2.0, ex4::Emotion::PERPLEXED }
  };

  CHECK(expected == blobs);
}



