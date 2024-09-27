/**
 * @author mock
 * v1.0
 * SoSe 2020
 */

import java.util.HashSet;
import java.util.Set;

public class CacheSimulator {

    private final int cacheLines;
    private final int associativity;
    private final int blockSize;
    private final String filename;
    private final boolean verbose;
    private final ValgrindLineParser valgrindParser;

    private Cache cache;

    CacheSimulator(int cacheLines, int associativity, int blockSize, String filename, boolean verbose) {
        this.cacheLines = cacheLines;
        this.associativity = associativity;
        this.blockSize = blockSize;
        this.filename = filename;
        this.verbose = verbose;
        valgrindParser = new ValgrindLineParser(filename);
        this.cache = new Cache(cacheLines, blockSize);
        setup();  // do some setup stuff before the simulation

    }

    private void setup() {
	// TODO prepare the simulation

    }
    public void simulate() {
        ValgrindLineParser.ValgrindLine line = null;
        Set<Integer> sizes = new HashSet<Integer>();

        while ((line = valgrindParser.getNext()) != null) {
            long clock = valgrindParser.getLineNumber();  // we use the line number as a logical clock 
            sizes.add(line.size);
            switch (line.accessKind) {
                case 'L':
                    simulateLoad(line, clock);
                    break;
                case 'M':
                    simulateLoad(line, clock);
                    simulateStore(line, clock);
;                    break;
                case 'S':
                    simulateStore(line, clock);
                    break;
                case 'I':
                    // nothing to do for D cache
                    break;
                default:
                    // hmm that should not happen
                    System.out.println("Don't know how to simulate access kind " + line.accessKind);
                    break;
            }

        }
        System.out.println("Successfully simulated " + valgrindParser.getLineNumber() + " valgrind lines");
        System.out.println("Access sizes in trace: ");
        for (int size : sizes) {
            System.out.print(size + " ");
        }
        System.out.println("");
        // TODO Hier geben Sie die Gesamtstatistik aus
        System.out.println("hits: " + cache.getHits() + " misses: " + cache.getMiss() + " evictions: " + cache.getEviction());
        if (verbose) {
            System.out.println("Dumping cache content:");
            cache.dumping();

        }
    }

    public int log2(int x) {
        int result = 0;
        while (x > 1) {
            result ++;
            x = x >> 1;
        }
        return result;
    }

    private void simulateStore(ValgrindLineParser.ValgrindLine line, long clock) {
        if (verbose) {
            System.out.print("store " + Long.toString(line.address, 16) + " " + line.size);
        }
        simulateAccess(line, clock);
    }

    private void simulateLoad(ValgrindLineParser.ValgrindLine line, long clock) {
        if (verbose) {
            System.out.print("load " + Long.toString(line.address, 16) + " " + line.size);
        }
        simulateAccess(line, clock);

    }

    private void simulateAccess(ValgrindLineParser.ValgrindLine line, long clock) {
        // TOOD the main part 
        if (cache.access(line, verbose)) {
            if (verbose) {
                System.out.println(" hit");
            }
        } else {
            if (verbose) {
                System.out.println(" miss");
            }
        }
    }



}
