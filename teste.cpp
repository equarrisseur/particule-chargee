 TApplication theApp("App", &argc, argv);  
  
  int N = 100;
 // double xmin = 0, xmax = 2*M_PI;  
//  double h = (xmax-xmin)/N;
  
  TCanvas c1("c1","dessin",900,700);  //Canvas pour dessiner
//  c1.SetLogy(); // Pour afficher la figure avec un axe des ordonnees en echelle log

  TFile *fichier_root=TFile::Open("CosSin.root","RECREATE");

  TGraph graphe_sinus(N); // crée un graphe de nom graphe_sinus avec 100 points
  

  graphe_sinus.SetName("sinus"); // nom sans espace (sous lequel il sera sauvé)
  graphe_sinus.SetTitle("sinus"); // donne un titre au graphe graphe_sinus
  graphe_sinus.SetMarkerColor(2); // donne une couleur (rouge) aux points du graphe
  graphe_sinus.SetMarkerStyle(20); // change la forme des points du graphe
  graphe_sinus.SetLineColor(2); // donne la même couleur à la ligne qui relie les points
  graphe_sinus.SetFillColor(0); // couleur de remplissage blanc
  
 

  // Boucle de remplisssage des TGraph
  for(int i=0; i<N; i++){
    double x = i*h;
    graphe_sinus.SetPoint(i,x,sin(x)); // donne les coordonnées x (abscisse) et (ordonnée) sin(x) au ieme point.
    
  }
  
  // Trace des 2 fonctions sur une meme figure
  graphe_sinus.Draw("ALP"); //A pour nouveau dessin, L pour avoir une ligne entre les points, P pour voir les points
 
 
  (graphe_sinus.GetXaxis())->SetTitle("X"); // on ajoute l'information sur l'axe X
  
  // Definition de la legende
  TLegend *leg=gPad->BuildLegend();
  leg->SetFillColor(0);
  
  
  graphe_sinus.Write();
 

  graphe_sinus.SetTitle("sinus et cosinus"); // change le titre du graphe graphe_sinus après avoir fait la legende
  
  
  // Enregistrement de la figure 
  c1.SaveAs("SinCos.png");
   
  fichier_root->Close();  
  
  // Affichage des figures si mode interactif (pas en mode batch)
  if(!gROOT->IsBatch()) theApp.Run();     
  
