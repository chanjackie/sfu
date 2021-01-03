package sfu.cmpt213.as1;

public class Tokimon {

    private String name;
    private String type;
    private double height;
    private double weight;
    private int strength;

    public Tokimon(String name, String type, double height, double weight) {
        this.name = name;
        this.type = type;
        this.height = height;
        this.weight = weight;
        this.strength = 0;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public double getHeight() {
        return height;
    }

    public void setHeight(double height) {
        this.height = height;
    }

    public double getWeight() {
        return weight;
    }

    public void setWeight(double weight) {
        this.weight = weight;
    }

    public int getStrength() {
        return strength;
    }

    public void addStrength(int strength) {
        this.strength = Math.min(this.strength+strength, 100);
        this.strength = Math.max(this.strength, 0);
        System.out.printf("%s now has strength %d!", this.name, this.strength);
    }

    // overriding the toString() method
    public String toString() {
        String object = Tokimon.class.getName();
        object += "(Name: " + this.name + ", Type: " + this.type + ", Height: " + this.height +
                ", Weight: " + this.weight + ", Strength: " + this.strength + ")";
        return object;
    }
}
