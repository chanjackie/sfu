package ca.cmpt213.as2;

import com.google.gson.Gson;

import java.io.File;
import java.io.FileFilter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Objects;

/**
 * TokimonProcessor class is responsible for receiving .json input files and processing
 * them to create Java objects containing all information in the .json file.
 */
public class TokimonProcessor {

    public static void main(String[] args) {
        if (!verifyInputArgs(args)) {
            System.exit(-1);
        }
        ArrayList<File> files = getJsonFiles(args[0]);
        ArrayList<TokimonTeam> tokimonTeams = getTokimonTeamsFromJson(files);
        tokimonTeams.sort(new TokimonTeamSorter());
        checkValidTeams(tokimonTeams);
        TeamCSVWriter.writeToCsv(tokimonTeams, args[1]);
    }

    private static void checkValidTeams(ArrayList<TokimonTeam> tokimonTeams) {
        HashMap<String, String> tokiIdToName = new HashMap<>();
        for (TokimonTeam team : tokimonTeams) {
            if (team.getTeamNum() == null || team.getLeaderId() == null || team.getExtraComments() == null) {
                System.out.println("Incorrect JSON file. Please check that all necessary fields are present and properly formatted.");
                System.exit(-1);
            }
            for (Tokimon toki : team.getTeam()) {
                if (toki.getCompatibility().getScore() < 0) {
                    System.out.println("Score for " + toki.getId() + " in team " + team.getLeaderId() + " should not be negative.");
                    System.exit(-1);
                }
                if (!tokiIdToName.containsKey(toki.getId())) {
                    tokiIdToName.put(toki.getId(), toki.getName());
                } else {
                    if (!tokiIdToName.get(toki.getId()).equalsIgnoreCase(toki.getName())) {
                        System.out.println("Toki " + toki.getId() + " should have the same name in all JSON files.");
                        System.exit(-1);
                    }
                }
            }
        }

    }

    private static ArrayList<TokimonTeam> getTokimonTeamsFromJson(ArrayList<File> files) {
        Gson gson = new Gson();
        ArrayList<TokimonTeam> tokimonTeams = new ArrayList<>();
        for (File file : files) {
            try {
                String json = Files.readString(file.toPath());
                TokimonTeam team = gson.fromJson(json, TokimonTeam.class);
                team.sortTeam();
                tokimonTeams.add(team);
            } catch (IOException e) {
                e.printStackTrace();
                System.exit(-1);
            }
        }
        return tokimonTeams;
    }

    private static ArrayList<File> getJsonFiles(String pathname) {
        ArrayList<File> files = new ArrayList<>();
        FileFilter jsonFilter = new JsonFilter();
        File inputFolder = new File(pathname);
        File[] jsonFolders = inputFolder.listFiles();

        if (jsonFolders != null) {
            for (File file : jsonFolders) {
                File[] jsons = file.listFiles(jsonFilter);
                files.addAll(Arrays.asList(Objects.requireNonNull(jsons)));
            }
        }
        return files;
    }

    private static boolean verifyInputArgs(String[] args) {
        if (args.length != 2) {
            System.out.println("Expected 2 arguments: \n" +
                    "1. Path to the directory containing the input .JSON files.\n" +
                    "2. Path to the output directory where the generated .csv will be placed.");
            return false;
        }
        for (String path : args) {
            if (Files.notExists(Path.of(path))) {
                System.out.printf("%s does not exist.\n", path);
                return false;
            }
        }
        return true;
    }
}
