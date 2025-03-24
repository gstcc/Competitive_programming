import java.util.*;

public class SetStack {
    static int counter = 0;
    static Stack<Set<Object>> stack = new Stack<>();
    static Map<Set<Object>, Object> objToIdentifier;


    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in); // Using Scanner for input
        int ts = sc.nextInt();
        for (int test = 0; test < ts; test++) {
            int operations = sc.nextInt();
            objToIdentifier = new HashMap<>();
            for (int op = 0; op < operations; op++) {
                String operation = sc.next();
                switch (operation) {
                    case "PUSH":
                        push();
                        break;
                    case "DUP":
                        dup();
                        break;
                    case "UNION":
                        union();
                        break;
                    case "INTERSECT":
                        intersect();
                        break;
                    default: // Add
                        add();
                        break;
                }
                System.out.println(stack.peek().size());
            }
            System.out.println("***");
            stack.clear();
        }
        sc.close();
    }

    static void push() {
        stack.add(new HashSet<>());
    }

    static void dup() {
        Set<Object> set = stack.pop();
        stack.push(set);
        stack.push(set);
    }

    static void union() {
        Set<Object> lh = stack.pop();
        Set<Object> rh = stack.pop();

        lh.addAll(rh);
        stack.add(lh);
    }

    static void intersect() {
        Set<Object> lh = stack.pop();
        Set<Object> rh = stack.pop();
        lh.retainAll(rh);
        stack.add(lh);
    }

    /*
     * Instead of adding objects so they are nestled, we instead just represent each one as 
     * a number. This way each one is objToIdentifier and we can easily just add them
     */
    static void add() {
        Set<Object> lh = stack.pop();
        Set<Object> rh = stack.pop();

        Set<Object> set = new HashSet<>();

        if(!objToIdentifier.containsKey(lh)) {
            objToIdentifier.put(lh, counter);
            set.add(counter);
            counter++;
        } else {
            set.add(objToIdentifier.get(lh));
        }

        set.addAll(rh);
        stack.add(set);
    }
}