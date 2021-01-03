package ca.cmpt213.asn5.server.model;

/**
 * Tokimon class responsible for providing model for Tokimon object.
 */

public class Tokimon {

    private long id;
    private String name;
    private double weight;
    private double height;
    private String ability;
    private int strength;
    private String color;

    public Tokimon(String nme, double wt, double ht, String ablty, int str, String clr) {
        this.id = 0;
        this.name = nme;
        this.weight = wt;
        this.height = ht;
        this.ability = ablty;
        this.strength = str;
        this.color = clr;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public double getWeight() {
        return weight;
    }

    public void setWeight(double weight) {
        this.weight = weight;
    }

    public double getHeight() {
        return height;
    }

    public void setHeight(double height) {
        this.height = height;
    }

    public String getAbility() {
        return ability;
    }

    public void setAbility(String ability) {
        this.ability = ability;
    }

    public int getStrength() {
        return strength;
    }

    public void setStrength(int strength) {
        this.strength = strength;
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }

}
