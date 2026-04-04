package es.uned.lsi.eped.pract2025_2026;

import es.uned.lsi.eped.DataStructures.SequenceIF;
import es.uned.lsi.eped.DataStructures.IteratorIF;
import es.uned.lsi.eped.DataStructures.Queue;

public class Seq_PSF {
    private SequenceIF<Pair_S_F> seqStringFreq;
    
    /* Constructor */
    public Seq_PSF() {
        this.seqStringFreq = new Queue<Pair_S_F>();
    }

    /* Devuelve un iterador de la secuencia */
    public IteratorIF<Pair_S_F> iterator() {
        return this.seqStringFreq.iterator();
    }
    
    /* Añade un nuevo par <cadena,frecuencia> a la secuencia */
    public void add(Pair_S_F pair) {
        ((Queue<Pair_S_F>) this.seqStringFreq).enqueue(pair);
    }
}

