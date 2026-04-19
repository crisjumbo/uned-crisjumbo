package es.uned.lsi.eped.pract2025_2026;

import es.uned.lsi.eped.DataStructures.SequenceIF;
import es.uned.lsi.eped.DataStructures.IteratorIF;
import es.uned.lsi.eped.DataStructures.List;

public class Seq_PSF {
    private SequenceIF<Pair_S_F> seqStringFreq;
    
    /* Constructor */
    public Seq_PSF() {
        this.seqStringFreq = new List<Pair_S_F>();
    }

    /* Devuelve un iterador de la secuencia */
    public IteratorIF<Pair_S_F> iterator() {
        return this.seqStringFreq.iterator();
    }
    
    /* Añade un nuevo par <cadena,frecuencia> a la secuencia */
    public void add(Pair_S_F pair) {
    	int pos;
    	
    	pos = 1;
    	if (this.seqStringFreq.isEmpty()) {
    		((List<Pair_S_F>) this.seqStringFreq).insert(pos, pair);
    	} else {
    		pos = this.seqStringFreq.size() + 1;
    		((List<Pair_S_F>) this.seqStringFreq).insert(pos, pair);
    	}
    }
}

