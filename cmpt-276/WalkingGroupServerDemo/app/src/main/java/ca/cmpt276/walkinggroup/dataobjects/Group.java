package ca.cmpt276.walkinggroup.dataobjects;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

@JsonIgnoreProperties(ignoreUnknown = true)
public class Group  extends IdItemBase {
    private String groupDescription;

    // Route points (meeting to target)
    private double[] routeLatArray = new double[0];
    private double[] routeLngArray = new double[0];

    private User leader;
    private Set<User> memberUsers = new HashSet<>();
    private String customJson;



    public String getGroupDescription() {
        return groupDescription;
    }

    public void setGroupDescription(String groupDescription) {
        this.groupDescription = groupDescription;
    }

    public double[] getRouteLatArray() {
        return routeLatArray;
    }

    public void setRouteLatArray(double[] routeLatArray) {
        this.routeLatArray = routeLatArray;
    }

    public double[] getRouteLngArray() {
        return routeLngArray;
    }

    public void setRouteLngArray(double[] routeLngArray) {
        this.routeLngArray = routeLngArray;
    }

    public User getLeader() {
        return leader;
    }

    public void setLeader(User leader) {
        this.leader = leader;
    }

    public Set<User> getMemberUsers() {
        return memberUsers;
    }

    public void setMemberUsers(Set<User> memberUsers) {
        this.memberUsers = memberUsers;
    }

    public String getCustomJson() {
        return customJson;
    }

    public void setCustomJson(String customJson) {
        this.customJson = customJson;
    }

    @Override
    public String toString() {
        return "Group{" +
                "groupDescription='" + groupDescription + '\'' +
                ", routeLatArray=" + Arrays.toString(routeLatArray) +
                ", routeLngArray=" + Arrays.toString(routeLngArray) +
                ", leader=" + leader +
                ", memberUsers=" + memberUsers +
                ", customJson='" + customJson + '\'' +
                ", id=" + id +
                ", hasFullData=" + hasFullData +
                ", href='" + href + '\'' +
                '}';
    }
}
