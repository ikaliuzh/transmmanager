# transmmanager
Test Task

Formula to compute relevance of a particular path. 

  Let  `S = {P \in Paths | P connects initial and final stations and it is at least 15min gap between arrival and next departure}`
then 
  `relevance(P) = 1/P.n * log(P.total_time * P.total_price / MaxPrice * MaxTime)`,
where P.n is the number of transfers,
      `MaxPrice = max{P.total_price | P \in S}`,
      `MaxTime = max{P.total_time | P \in S}`. 
