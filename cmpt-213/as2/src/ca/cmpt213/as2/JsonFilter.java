package ca.cmpt213.as2;

import java.io.File;
import java.io.FileFilter;

/**
 * JsonFilter class is responsible for implementing an
 * instance of FileFilter which filters out non-json files.
 */
public class JsonFilter implements FileFilter {
    @Override
    public boolean accept(File pathname) {
        return pathname.getName().endsWith(".json");
    }
}
