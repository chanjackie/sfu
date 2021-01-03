package ca.cmpt213.as2;

import java.io.FileFilter;
import java.util.ArrayList;

public class Main {


    @PostMapping("/api/bike/add")
    public Bike addBike(@RequestBody Bike newBike) {
        if (manager.contains(newBike)) {
            throw new BadArgumentException("This bike is already present!");
        } else {
            manager.addBike(newBike);
        }
        return newBike;
    }

    @GetMapping("/api/bike/{id}")
    public Bike getBike(@PathVariable long id) {
        Filter filter = new FilterImpl();
        List<Bike> filteredBikes = manager.getFiltered(filter);
        for (Bike bike : filteredBikes) {
            if (bike.getId() == id) {
                return bike;
            }
        }
        throw new IllegalArgumentException("Could not find bike with id: " + id);
        return null;
    }
}
