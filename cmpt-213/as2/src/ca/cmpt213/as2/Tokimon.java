package ca.cmpt213.as2;

/**
 * Tokimon class is responsible for holding the information of
 * each Tokimon in a team, including its name, id, and compatibility
 * with the team.
 */
public class Tokimon {
    private String name;
    private String id;
    private Compatibility compatibility;

    public Tokimon(String n, String i, Compatibility compat) {
        name = n.trim();
        id = i.trim();
        compatibility = compat;
    }

    public String getName() {
        return name;
    }

    public String getId() {
        return id;
    }

    public Compatibility getCompatibility() {
        return compatibility;
    }

    /**
     * Compatibility class is a nested class containing the
     * compatibility score of its respective Tokimon, as well
     * as the comment.
     */
    public static class Compatibility {
        private float score;
        private String comment;

        public Compatibility(float sc, String cmnt) {
            score = sc;
            comment = cmnt;
        }

        public float getScore() {
            return score;
        }

        public String getComment() {
            return comment;
        }
    }
}
