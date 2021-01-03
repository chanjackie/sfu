package ca.cmpt213.as2;

import java.util.Comparator;

/**
 * TokimonTeamSorter class is responsible for implementing a Comparator,
 * used for sorting TokimonTeams by each team's teamNum field.
 */
public class TokimonTeamSorter implements Comparator<TokimonTeam> {
    @Override
    public int compare(TokimonTeam t1, TokimonTeam t2) {
        return t1.getTeamNum().compareTo(t2.getTeamNum());
    }
}