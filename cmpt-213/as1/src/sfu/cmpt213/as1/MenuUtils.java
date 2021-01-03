package sfu.cmpt213.as1;

import java.util.ArrayList;
import java.util.Scanner;

public final class MenuUtils {

    public static void printHeader(String title) {
        String border = new String(new char[title.length() + 4]).replace("\0", "*");
        title = "* " + title + " *";
        System.out.println("\n" + border + "\n" + title + "\n" + border);
    }

    public static void displayMainMenu() {
        printHeader("Main Menu");
        System.out.println(
                "  _____     _    _                       \n" +
                " |_   _|__ | | _(_)_ __ ___   ___  _ __  \n" +
                "   | |/ _ \\| |/ / | '_ ` _ \\ / _ \\| '_ \\ \n" +
                "   | | (_) |   <| | | | | | | (_) | | | |\n" +
                "   |_|\\___/|_|\\_\\_|_| |_| |_|\\___/|_| |_|\n" +
                "                                         ");
        System.out.println(
                "1. List Tokimons\n" +
                "2. Add a new Tokimon\n" +
                "3. Remove a Tokimon\n" +
                "4. Modify Tokimon strength\n" +
                "5. DEBUG: Dump tokimons (toString)\n" +
                "6. Exit");
    }

    public static void displayAllTokis(Tokidex tokidex) {
        ArrayList<Tokimon> tokimonList = tokidex.getTokimonList();
        if (tokimonList.isEmpty()) {
            System.out.println("There are no Tokimons in your Tokidex.");
            return;
        }
        printHeader("List of Tokimons:");
        for (int i = 0; i < tokimonList.size(); i++) {
            Tokimon toki = tokimonList.get(i);
            System.out.printf("%d. %s, %s ability, %.2fm, %.1fkg, %d strength%n", i+1, toki.getName(),
                    toki.getType(), toki.getHeight(), toki.getWeight(), toki.getStrength());
        }
    }

    public static void addNewToki(Tokidex tokidex) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter Tokimon's name:  ");
        String name = sc.next();
        System.out.print("Enter Tokimon's type:  ");
        String type = sc.next();
        System.out.print("Enter Tokimon's height (m):  ");
        double height = sc.nextDouble();
        System.out.print("Enter Tokimon's weight (kg):  ");
        double weight = sc.nextDouble();
        tokidex.addToki(name, type, height, weight);
    }

    private static int selectToki(Tokidex tokidex, String prompt) {
        Scanner sc = new Scanner(System.in);
        displayAllTokis(tokidex);
        int index;
        while (true) {
            System.out.print(prompt);
            index = sc.nextInt();
            if (index < 0 || index > tokidex.getTokimonList().size()) {
                System.out.println("Please select a valid Tokimon.");
            } else {
                return index;
            }
        }
    }

    public static void deleteToki(Tokidex tokidex) {
        String prompt = "Select a Tokimon to remove (0 to cancel):  ";
        int index = selectToki(tokidex, prompt);
        if (index != 0) {
            tokidex.removeToki(index-1);
        }
    }

    public static void alterToki(Tokidex tokidex) {
        Scanner sc = new Scanner(System.in);
        String prompt = "Select a Tokimon to strengthen (0 to cancel):  ";
        int index = selectToki(tokidex, prompt);
        int strength;
        if (index != 0) {
            System.out.print("By how much? (0 to cancel):  ");
            strength = sc.nextInt();
            if (strength != 0) {
                tokidex.updateTokimon(index-1, strength);
            }
        }
    }

    public static void dumpTokis(Tokidex tokidex) {
        ArrayList<Tokimon> tokimonList = tokidex.getTokimonList();
        printHeader("DEBUG: All Tokimon objects");
        for (int i = 0; i < tokimonList.size(); i++) {
            Tokimon toki = tokimonList.get(i);
            System.out.printf("%d. %s\n", i+1, toki.toString());
        }
    }
}
