package sfu.cmpt213.as1;

import java.util.ArrayList;

public class Tokidex {

    private final ArrayList<Tokimon> tokimonList;

    public Tokidex() {
        this.tokimonList = new ArrayList<Tokimon>();
    }

    public ArrayList<Tokimon> getTokimonList() {
        return tokimonList;
    }

    public void addToki(String name, String type, double height, double weight) {
        Tokimon newToki = new Tokimon(name, type, height, weight);
        this.tokimonList.add(newToki);
    }

    public void removeToki(int index) {
        System.out.printf("%s has been removed!", tokimonList.get(index).getName());
        this.tokimonList.remove(index);
    }

    public void updateTokimon(int index, int strength) {
        this.tokimonList.get(index).addStrength(strength);
    }
}
