
public class Cache {
    private int indexbits;
    private int blockbits;
    private int[] index;
    private long[] tag;
    private boolean[] v;

    private int hit = 0;
    private int miss = 0;
    private int eviction = 0;

    public Cache(int indexbits, int blockbits) {
        this.indexbits = indexbits;
        this.blockbits = blockbits;
        this.tag = new long[indexbits];
        this.v = new boolean[indexbits];

        for (int k = 0; k < indexbits; ++k) {
            this.tag[k] = 0;
            this.v[k] = false;
        }
    }

    public boolean access(ValgrindLineParser.ValgrindLine line, boolean verbose) {
        int index = (int) (line.address / blockbits) % indexbits;
        long tag = line.address >> (log2(blockbits) + log2(indexbits));

        // System.out.print(" " + Long.toString(index) + "_");

        if (this.v[index]) {
            if (this.tag[index] == tag)  {
                this.hit += 1;
                return true;
            }
            this.tag[index] = tag;
            this.miss += 1;
            this.eviction += 1;
            if (verbose) {
                System.out.print(" eviction");
            }
            return false;
        } else {
            this.tag[index] = tag;
            this.v[index] = true;
            this.miss += 1;
            return false;
        }
    }

    public static int log2(int x) {
        int result = 0;
        while (x > 1) {
            result ++;
            x = x >> 1;
        }
        return result;
    }

    public int getHits() {
        return this.hit;
    }

    public int getMiss() {
        return this.miss;
    }

    public int getEviction() {
        return this.eviction;
    }

    public void dumping() {
        for (int k = 0; k < indexbits; ++k) {
            System.out.println("index: " + k  + " " + this.tag[k]);
        }
    }
}
