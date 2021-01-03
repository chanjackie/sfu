package ca.cmpt213.as2;

import java.util.Comparator;

/**
 * TokimonSorter class is responsible for implementing a
 * Comparator, used for sorting teams by each Tokimon's id.
 */
public class TokimonSorter implements Comparator<Tokimon> {
    @Override
    public int compare(Tokimon t1, Tokimon t2) {
        return t1.getId().compareTo(t2.getId());
    }
}
