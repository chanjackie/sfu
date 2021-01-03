package ca.cmpt213.as2;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * TeamCSVWriter class responsible for writing processed
 * TokimonTeam objects to a .csv file containing team info.
 */
public class TeamCSVWriter {
    public static final String[] ENTRIES = {
            "Team#,",
            "From Toki,",
            "To Toki,",
            "Score,",
            "Comment,",
            ",",
            "Extra\n"
    };
    public static final String CSVNAME = "team_info.csv";

    public static void writeToCsv(ArrayList<TokimonTeam> teams, String outdir) {
        if (!outdir.endsWith("/")) {
            outdir += "/";
        }
        try {
            FileWriter csvWriter = new FileWriter(outdir + CSVNAME);
            for (String e : ENTRIES) {
                csvWriter.append(e);
            }

            List<String> teamNums = new ArrayList<>();
            int teamCount = 0;
            for (TokimonTeam team : teams) {
                String teamNum = team.getTeamNum();
                String leaderId = team.getLeaderId();
                // Write new 'Team' header if new team.
                if (!teamNums.contains(teamNum)) {
                    teamNums.add(teamNum);
                    teamCount++;
                    if (teamCount > 1) {
                        csvWriter.append("\n,,,,,,\n");
                    }
                    csvWriter.append("Team ").append(String.valueOf(teamCount)).append(",,,,,,");
                }
                for (Tokimon toki : team.getTeam()) {
                    csvWriter.append("\n,").append(leaderId).append(",");
                    if (toki.getId().equalsIgnoreCase(leaderId)) {
                        csvWriter.append("-,");
                    } else {
                        csvWriter.append(toki.getId()).append(",");
                    }
                    csvWriter.append(String.valueOf(toki.getCompatibility().getScore())).append(",");
                    csvWriter.append("\"").append(toki.getCompatibility().getComment()).append("\"").append(",,");
                }
                csvWriter.append(team.getExtraComments());
            }
            csvWriter.flush();
            csvWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }
}
