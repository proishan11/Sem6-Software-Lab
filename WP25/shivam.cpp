string get_regex() {

    get_intermediate_states();

    vector <string> from, to;
    
    for(int i = 0; i < intermediate.size(); i++) {
        
        from = get_from_states(intermediate[i]);
        to = get_to_states(intermediate[i]);

        for(int j = 0; j < from.size(); j++) {
            for(int k = 0; k < to.size(); k++) {
                string loop = get_loop(intermediate[i]);
                string update = "";

                // update += "(" + gtg[get_index(from[j])][get_index(to[k])] + ")+" ;
                update += gtg[get_index(from[j])][get_index(to[k])] + " + " ;
                
                // update += "(" + gtg[get_index(from[j])][get_index(intermediate[i])] + ")";
                update += gtg[get_index(from[j])][get_index(intermediate[i])];
                
                if(loop.length()) {
                    update += "(" + loop + ")*";
                    // update += loop + "*";
                } 
                // update += "(" + gtg[get_index(intermediate[i])][get_index(to[k])] + ")";
                update += gtg[get_index(intermediate[i])][get_index(to[k])];

                gtg[get_index(from[j])][get_index(to[k])] = get_corrected(update);

            }
        }
    
        print_gtg();

    }