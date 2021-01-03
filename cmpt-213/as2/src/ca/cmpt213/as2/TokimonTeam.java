package ca.cmpt213.as2;

import java.util.ArrayList;
import java.util.Arrays;

/**
 * TokimonTeam class is responsible for holding each team's information
 * its respective json file, including its leader, its members, and
 * its extra comments.
 */
public class TokimonTeam {

    private ArrayList<Tokimon> team;
    private String leaderId;
    private String teamNum;
    private String extra_comments;

    public TokimonTeam(Tokimon[] tokis, String comments) {
        team = new ArrayList<>();
        team.addAll(Arrays.asList(tokis));
        extra_comments = comments;
    }

    public ArrayList<Tokimon> getTeam() {
        return team;
    }

    public String getExtraComments() {
        return extra_comments;
    }

    public String getLeaderId() {
        return leaderId;
    }

    public String getTeamNum() {
        return teamNum;
    }

    public void sortTeam() {
        Tokimon lead = team.remove(0);
        team.sort(new TokimonSorter());
        team.add(lead);
        leaderId = lead.getId();
        teamNum = lead.getId().substring(4, 6);
    }

    @Override
    public String toString() {
        StringBuilder teamString = new StringBuilder();
        for (Tokimon toki : team) {
            teamString.append("id: ").append(toki.getId()).append(", score: ").append(toki.getCompatibility().getScore()).append(", ");
            teamString.append(toki.getCompatibility().getComment()).append("\n");
        }
        return String.valueOf(teamString.append(extra_comments));
    }
}
