 UCI options description
  
  o["Debug Log File"]          << Option("", on_logger);
  
  /*  
	  The "Contempt" option has the default set to zero , but you can find good success with a setting of minus 10 to minus 30. Minus 10 would be used for stronger engines like Komodo and Houdini, for most other engines minus 30 is fine. A setting of as low as a plus 10 will help in securing a draw if needed. It's used for game and not analysis.
	  Contempt=18 (not default), in particular, is very good for particular openings: Scandinavian Defense, Benoni, Rubinstein and Tromposky... The C version has the contempt's range from -100 to +100.
  
  */
  o["Contempt"]               << Option(0, -300, 300);
  /* White_Contempt is to be used for analysis when someone wants to main the "respect" setting from the White POV. The Contempt parameters were increased from -100 to 100 to -300 to 300.  
  The C version has the contempt's range from -100 to +100.*/  
  o["White_Contempt"]         << Option(0, -300, 300);
  //best: set to logical cores
  o["Threads"]                 << Option(n, 1, 512, on_threads);
  /*
    hash tables to set based on the formula M=2nft where
    M=hash tables size in kb
	n=number of threads
	f=single processor frequence (kb)
	t=average time for move (seconds)
  */
  o["Hash"]                    << Option(128, 1, MaxHashMB, on_hash_size);
  /*
   Self explanatory. Click the button to manually clear the hash, if that's what you want to do. I usually only use this if I'm running manual analysis on a position and need to restart the engine with no previous lines in the hash memory.
  */
  o["Clear Hash"]              << Option(on_clear_hash);
  /*
	If you're playing two engines against each other, It's recommended you use "ponder off". If you're playing against the engine and you want the engine to think on your own time, then use "ponder on".
  */
  o["Ponder"]                  << Option(false);
  o["MultiPV"]                 << Option(1, 1, 500);
  o["Skill Level"]             << Option(20, 0, 20);
  
  //Time manager
  o["Time manager"]          << Option();
  /*
	"Move Overhead" This is designed to compensate for slow user interfaces, where a
	fraction of a second can be lost in the processing and transferring of
	information back and forth from the engine to the interface.  This
	should probably be left alone unless you see the program starting to
	forfeit games due to exhausting its time.
  */
  o["Move Overhead"]           << Option(100, 0, 5000);
  //"Minimum Thinking Time"=The minimum amount of time to analyze, in milliseconds
  o["Minimum Thinking Time"]    << Option(20, 0, 5000);
  /*
    "Slow Mover"  when increasing the value you make SF to think more, decreasing (down to 10 that is the minimum) you make SF to move faster. That is what is called "Time usage percent" in the Shredder engine. Default value is 100. With lower valus it plays faster, with higher values slower - of course always within the time control. It had an effect in Shredder 10. With little faster time control (95) it plays about 20 ELo better in Ponder ON Games back then - but the effect was not visible in Ponder off games
   */ 
  o["Slow Mover"]               << Option(89, 10, 1000);
  /*
    "nodestime"=size of an internal FIFO called measured_nps, that is
    initialized with zero values. 
  */
  o["nodestime"]               << Option(0, 0, 10000);
  /*
   "play fast" option when mate is found for quicker play. This mostly useful in engine vs engine play to speed up play.
  */
  o["FastPlay"]                << Option(false);
  
  //Hash file management
  o["Hash file management"]          << Option();
  o["NeverClearHash"]		   << Option(false);
  o["HashFile"]		           << Option("hash.hsh", on_HashFile);
  o["SaveHashtoFile"]		   << Option(SaveHashtoFile);
  o["LoadHashfromFile"]		   << Option(LoadHashfromFile);
  o["LoadEpdToHash"]            << Option(LoadEpdToHash);
  //Chess 960
  o["UCI_Chess960"]            << Option(false); 
  
  //Sygyzy section
  o["Sygyzy section"]          << Option();
  o["SyzygyPath"]              << Option("<empty>", on_tb_path);
  o["SyzygyProbeDepth"]        << Option(1, 1, 100);
  o["Syzygy50MoveRule"]        << Option(true);
  o["SyzygyProbeLimit"]        << Option(6, 0, 6);
  
  //Large Pages
  o["Large Pages"]             << Option(true, on_large_pages);
  
  //Correspondence section
  o["Correspondence Chess Analyzer"]     << Option();
  //Analysis Mode widen the search and may help in certain positions: not for game play!
  o["Analysis Mode"]     << Option(false);
  /*	
   The "BruteForce" option eliminates all reductions, now excluding null moves (no null move, Razoring, Futility Pruning, ProbCut and LMR (see advanced section)). Like NullMove option may help in solving some chess puzzles. Setting "BruteForce" ON will enable the Stockfish-based engine to play like an engine from the early 90's. Other than setting the Contempt, the default settings are best for engine versus engine play
  */
  o["BruteForce"]            << Option(false);
  //like brute force it can help in solving some positions 
  o["NullMove"]                << Option(true);
  //per trovare la distanza dal matto anche quando la posizione sta nelle tabelle dei finali
  o["Clean Search"]            << Option(false);
  //add a little variety to the play
  o["Variety"]               << Option (0, 0, 8);
  //Polyglot Book management
  o["Polyglot Book management"] << Option();
  o["Best Book Move"]          << Option(false);
  o["Book File"]               << Option("book.bin");

  /*
    Strength reduction section
	UCI-LimitStrength is used to dummy down Stockfish to a playing range of 1500 to 2800 ELO. McBrain targets a nodes per second (NPS) approach in its UCI Limit Strength. It can play at it's weakest level at a target of 32 NPS to over 50,000 NPS - equivalent to playing a $3500 Revelation machine using the stockfish engine, with the added features. It's recommended to start playing at the lowest level at with at least 10 seconds per move and ALWAYS set threads to 1 using this feature. One also has the SF normal skill level from 0 ( lowest) to 20 ( full strength) to further increase variability in play as well as to weaken the ability of this very strong , not for many humans, chess engine. */
  o["Strength reduction section"]          << Option();
  o["UCI_LimitStrength"]     << Option(false);
  o["UCI_ELO"]               << Option(1500, 1500, 2800);

  /*Cerebellum Book Library
  Cerebellum book and code used by Brainfish - a SF based engine by Thomas Zipproth (http://www.zipproth.de) - with the Cerebellum book enabled it will play about 30 ELO stronger. Please be sure to download the latest Cerebellum book from Thomas Zipproth's website. This book is a must in any engine vs engine game. It can be used in conjunction with other GUI/polyglot books and it is very, very good. */
  o["Cerebellum Library"]       << Option();
  o["Book Move2 Probability"]   << Option(0, 0, 100, on_book_move2_prob);
  o["BookPath"]                 << Option("Cerebellum_Light.bin", on_brainbook_path);
  
  //Shashin section https://www.inforchess.com/download/Best%20Play.pdf
  o["Shashin model"]     << Option();
  o["Safety Evaluator"]        << Option(false);
  
  //Advanced search options
  o["Advanced search options"]      << Option();
  //razoring
  o["Razoring"]               << Option(true);
  //Futility pruning: child node
  o["Futility"]               << Option(true);
  //Pruning at shallow depth
  o["Pruning"]                << Option(true);
  /*
    ProbCut: If we have a good enough capture and a reduced search returns a value
    much above beta, we can (almost) safely prune the previous move.
  */
  o["ProbCut"]                << Option(true);
  /*
    Reduced depth search (LMR). If the move fails high it will be
    re-searched at full depth.
  */
  o["LMR"]                    << Option(true);
  //maximum reduction
  o["MaxLMReduction"]         << Option(10, 0, 20);
  
		
Thanks to Marco Zerbinati, ChessMan3, Ivan Ivic, Daniel Jose, Michael (Mike) Byrne, and the rest of Stockfish community.
	