package ca.cmpt213.asn5.server.controller;

import ca.cmpt213.asn5.server.model.Tokimon;
import com.google.gson.GsonBuilder;
import org.springframework.web.bind.annotation.*;

import com.google.gson.Gson;

import javax.annotation.PostConstruct;
import javax.servlet.http.HttpServletResponse;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.lang.reflect.Type;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.atomic.AtomicLong;

/**
 * TokimonController class responsible for providing endpoints for all tokimon requests
 */

@RestController
public class TokimonController {
    private final AtomicLong counter = new AtomicLong();
    private static final String PATH_TO_TOKIMON_JSON = System.getProperty("user.dir") + "\\data\\tokimon.json";
    private List<Tokimon> tokimons = new ArrayList<>();

    @GetMapping("/api/tokimon/all")
    public List<Tokimon> getAllTokimons() {
        return tokimons;
    }

    @GetMapping("/api/tokimon/{id}")
    public Tokimon getTokimon(@PathVariable long id) {
        System.out.println("GET REQUEST FOR TOKIMON WITH ID: " + id);
        for (Tokimon toki : tokimons) {
            if (toki.getId() == id) {
                return toki;
            }
        }
        return null;
    }

    @PostMapping("/api/tokimon/add")
    public void addTokimon(@RequestBody Tokimon newToki) {
        System.out.println("Added new Tokimon: " + newToki.getName());
        newToki.setId(counter.incrementAndGet());
        tokimons.add(newToki);
        writeToJson();
    }

    @PostMapping("/api/tokimon/change/{id}")
    public void changeTokimon(@PathVariable long id, @RequestBody Tokimon newToki, HttpServletResponse response) {
        int index = 0;
        for (Tokimon toki : tokimons) {
            if (toki.getId() == id) {
                break;
            }
            index++;
        }
        if (index < tokimons.size()) {
            newToki.setId(id);
            tokimons.set(index, newToki);
            writeToJson();
            response.setStatus(201);
        } else {
            response.setStatus(204);
        }
    }

    @DeleteMapping("/api/tokimon/{id}")
    public void deleteTokimon(@PathVariable long id, HttpServletResponse response) {
        response.setStatus(204);
        tokimons.removeIf(t -> (t.getId() == id));
        writeToJson();
    }

    @PostConstruct
    public void init() {
        File tokimonJson = new File(PATH_TO_TOKIMON_JSON);
        System.out.println(PATH_TO_TOKIMON_JSON);
        try {
            String json = Files.readString(tokimonJson.toPath());
            System.out.println(json);
            if (!json.isEmpty()) {
                Tokimon[] tokis = new Gson().fromJson(json, (Type) Tokimon[].class);
                tokimons.addAll(Arrays.asList(tokis));
                long max = 0;
                for (Tokimon toki : tokimons) {
                    if (toki.getId() > max) {
                        max = toki.getId();
                    }
                }
                counter.set(max);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void writeToJson() {
        Gson gson = new GsonBuilder().setPrettyPrinting().create();
        try(FileWriter writer = new FileWriter(PATH_TO_TOKIMON_JSON)) {
            gson.toJson(tokimons, writer);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
