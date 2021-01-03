#include "doctest.h"
#include "Support.h"
#include "task03.h"
#include "Garden.h"

using ex5::task3::Bloom;
using ex5::task3::Color;
using ex5::task3::Height;
using ex5::task3::Location;
using ex5::task3::RootGrowth;


namespace doctest {

template<class Base, class Tag>
struct StringMaker<ex5::task3::StrongAlias<Base,Tag>> {
  static String convert(const ex5::task3::StrongAlias<Base,Tag>& in) {
    return std::to_string(in.value).c_str();
  }
};

template<>
struct StringMaker<ex5::task3::Location> {
  static String convert(const ex5::task3::Location& in) {
    return (std::to_string(in.getRow())
      + ","
      + std::to_string(in.getColumn())).c_str();
  }
};

}


TEST_CASE("Basic Creation") {
  auto sunflower = createSunflower(Location{0,1}, Color::YELLOW);
  auto monotropaUniflora = createMycoheterotroph(Location{1,0}, Color::INDIGO);
  auto lily = createRafflesia(Location{1,1}, Color::RED);

  CHECK(Location{0,1} == sunflower->getLocation());
  CHECK(Location{1,0} == monotropaUniflora->getLocation());
  CHECK(Location{1,1} == lily->getLocation());

  CHECK(Bloom{0} == sunflower->getBloom());
  CHECK(Height{0} == sunflower->getHeight());
  CHECK(RootGrowth{0} == sunflower->getRootGrowth());
}


TEST_CASE("Sunflower -- growing alone") {
  auto sunflower = createSunflower(Location{10,10}, Color::YELLOW);
  Garden garden;

  CHECK(Bloom{0} == sunflower->getBloom());
  CHECK(Height{0} == sunflower->getHeight());
  CHECK(RootGrowth{0} == sunflower->getRootGrowth());

  sunflower->grow(garden);

  CHECK(Bloom{1} == sunflower->getBloom());
  CHECK(Height{2} == sunflower->getHeight());
  CHECK(RootGrowth{1} == sunflower->getRootGrowth());

  sunflower->grow(garden);

  CHECK(Bloom{2} == sunflower->getBloom());
  CHECK(Height{4} == sunflower->getHeight());
  CHECK(RootGrowth{2} == sunflower->getRootGrowth());
}


TEST_CASE("Sunflower -- growing with a tall neighbor") {
  Garden garden;
  auto makeTallFlower = [&garden] (Location location) {
    auto sunflower = createSunflower(location, Color::YELLOW);
    sunflower->grow(garden);
    sunflower->grow(garden);
    return sunflower;
  };
  auto north = makeTallFlower(Location{11,10});
  CHECK(Height{4} == north->getHeight());
  garden.plant(std::move(north));

  auto east = makeTallFlower(Location{10,11});
  CHECK(Height{4} == east->getHeight());
  garden.plant(std::move(east));

  auto northeast = makeTallFlower(Location{11,11});
  CHECK(Height{4} == northeast->getHeight());
  garden.plant(std::move(northeast));

  auto center = makeTallFlower(Location{10,10});
  CHECK(Height{0} == center->getHeight());
}


TEST_CASE("Mycoheterotroph -- growing alone") {
  auto myco = createMycoheterotroph(Location{10,10}, Color::YELLOW);
  Garden garden;

  CHECK(Bloom{0} == myco->getBloom());
  CHECK(Height{0} == myco->getHeight());
  CHECK(RootGrowth{0} == myco->getRootGrowth());

  myco->grow(garden);

  CHECK(Bloom{1} == myco->getBloom());
  CHECK(Height{1} == myco->getHeight());
  CHECK(RootGrowth{2} == myco->getRootGrowth());

  myco->grow(garden);

  CHECK(Bloom{1} == myco->getBloom());
  CHECK(Height{1} == myco->getHeight());
  CHECK(RootGrowth{4} == myco->getRootGrowth());
}


TEST_CASE("Mycoheterotroph -- growing among other roots") {
  Garden garden;
  auto makeRootyFlower = [&garden] (Location location) {
    auto myco = createMycoheterotroph(location, Color::WHITE);
    myco->grow(garden);
    return myco;
  };
  auto north     = makeRootyFlower(Location{11,10});
  auto east      = makeRootyFlower(Location{10,11});
  auto northeast = makeRootyFlower(Location{11,11});
  north->grow(garden);
  north->grow(garden);

  CHECK(RootGrowth{6} == north->getRootGrowth());
  CHECK(RootGrowth{2} == east->getRootGrowth());
  CHECK(RootGrowth{2} == northeast->getRootGrowth());

  auto* northPtr = north.get();
  auto* eastPtr = east.get();
  garden.plant(std::move(north));
  garden.plant(std::move(east));
  garden.plant(std::move(northeast));

  // The northern plant should be large enough to keep growing.
  // The eastern plant is too small to grow.
  northPtr->grow(garden);
  CHECK(RootGrowth{8} == northPtr->getRootGrowth());
  eastPtr->grow(garden);
  CHECK(RootGrowth{2} == eastPtr->getRootGrowth());

  auto center = makeRootyFlower(Location{10,10});
  CHECK(RootGrowth{0} == center->getRootGrowth());
}


TEST_CASE("Corpse Lily -- growing alone and together") {
  auto lily = createRafflesia(Location{10,10}, Color::RED);
  Garden garden;

  CHECK(Bloom{0} == lily->getBloom());
  CHECK(Height{0} == lily->getHeight());
  CHECK(RootGrowth{0} == lily->getRootGrowth());

  lily->grow(garden);

  CHECK(Bloom{2} == lily->getBloom());
  CHECK(Height{0} == lily->getHeight());
  CHECK(RootGrowth{0} == lily->getRootGrowth());

  lily->grow(garden);

  CHECK(Bloom{2} == lily->getBloom());
  CHECK(Height{0} == lily->getHeight());
  CHECK(RootGrowth{0} == lily->getRootGrowth());

  auto sunflower = createSunflower(Location{10,11}, Color::YELLOW);
  sunflower->grow(garden);
  sunflower->grow(garden);
  garden.plant(std::move(sunflower));

  lily->grow(garden);

  CHECK(Bloom{4} == lily->getBloom());
  CHECK(Height{0} == lily->getHeight());
  CHECK(RootGrowth{0} == lily->getRootGrowth());

  lily->grow(garden);

  CHECK(Bloom{6} == lily->getBloom());
  CHECK(Height{0} == lily->getHeight());
  CHECK(RootGrowth{0} == lily->getRootGrowth());
}


TEST_CASE("Spreading Sunflowers") {
  Garden garden;
  auto center = createSunflower(Location{10,10}, Color::YELLOW);

  std::unique_ptr<Flower> first = center->spread(garden);
  CHECK(Location{11, 10} == first->getLocation());
  garden.plant(std::move(first));

  std::unique_ptr<Flower> second = center->spread(garden);
  CHECK(Location{9, 10} == second->getLocation());
  garden.plant(std::move(second));

  CHECK(!center->spread(garden));
}


TEST_CASE("Spreading Mycoheterotrophs") {
  Garden garden;
  auto center = createMycoheterotroph (Location{10,10}, Color::WHITE);

  std::unique_ptr<Flower> first = center->spread(garden);
  CHECK(Location{11, 10} == first->getLocation());
  garden.plant(std::move(first));

  std::unique_ptr<Flower> second = center->spread(garden);
  CHECK(Location{11, 11} == second->getLocation());
  garden.plant(std::move(second));

  std::unique_ptr<Flower> third = center->spread(garden);
  CHECK(Location{10, 11} == third->getLocation());
  garden.plant(std::move(third));

  std::unique_ptr<Flower> fourth = center->spread(garden);
  CHECK(Location{9, 11} == fourth->getLocation());
  garden.plant(std::move(fourth));

  std::unique_ptr<Flower> fifth = center->spread(garden);
  CHECK(Location{9, 10} == fifth->getLocation());
  garden.plant(std::move(fifth));

  std::unique_ptr<Flower> sixth = center->spread(garden);
  CHECK(Location{9, 9} == sixth->getLocation());
  garden.plant(std::move(sixth));

  std::unique_ptr<Flower> seventh = center->spread(garden);
  CHECK(Location{10, 9} == seventh->getLocation());
  garden.plant(std::move(seventh));

  std::unique_ptr<Flower> eighth = center->spread(garden);
  CHECK(Location{11, 9} == eighth->getLocation());
  garden.plant(std::move(eighth));

  CHECK(!center->spread(garden));
}


TEST_CASE("Spreading Lilies") {
  Garden garden;
  auto center = createRafflesia(Location{10,10}, Color::RED);

  std::unique_ptr<Flower> first = center->spread(garden);
  CHECK(Location{10, 11} == first->getLocation());
  garden.plant(std::move(first));

  std::unique_ptr<Flower> second = center->spread(garden);
  CHECK(Location{10, 9} == second->getLocation());
  garden.plant(std::move(second));

  CHECK(!center->spread(garden));

}
