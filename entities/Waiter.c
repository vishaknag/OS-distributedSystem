CreateAllMV(){
	int index;
	char ordertakerstatusMV;
	char baggedMV;
	char dineTypeMV;
	char deliveredMV;
	char baggedMV;
	char myOTMV;
	char orderMV;
	char sixBurgerMV;
	char threeBurgerMV;
	char vegBurgerMV;
	char friesMV;
	char sodaMV;
	char tablesMV;
	char tableNoMV;
	char tokenNoMV;
	
	
	/* nextOrderTakerIndex */
	nextOrderTakerIndexMVi = CreateMV("nextOrderTakerIndex", 19);
	/* custServed */
	custServedMVi = CreateMV("custServed", 10);
	/* nextWaiterIndex */
	nextWaiterIndexMVi = CreateMV("nextWaiterIndex", 15);
	/* foodToBag */
	foodToBagMVi = CreateMV("foodToBag", 9);
	/* nextCustomerIndex */
	nextCustomerIndexMVi = CreateMV("nextCustomerIndex", 17);
	/* custLineLength */
	custLineLengthMVi = CreateMV("custLineLength", 14);
	/* managerLineLength */
	managerLineLengthMVi = CreateMV("managerLineLength", 17);
	/* tableAvailable */
	tableAvailableMVi = CreateMV("tableAvailable", 14);
	/* nextTokenNumber */
	nextTokenNumberMVi = CreateMV("nextTokenNumber", 15);
	/* moneyAtRestaurant */
	moneyAtRestaurantMVi = CreateMV("moneyAtRestaurant", 17);
	
	
	/* foodReadyData.sixBurger */
	readySixBurgerMVi = CreateMV("readySixBurger", 14);
	/* foodReadyData.threeeBurger */
	readyThreeBurgerMVi = CreateMV("readyThreeBurger", 16);
	/* foodReadyData.vegBurger */
	readyVegBurgerMVi = CreateMV("readySixVegBurger", 178);
	/* foodReadyData.fries */
	readyFriesMVi = CreateMV("readyFries", 10);

	/* foodToBeCookedData.sixBurger */
	toBeCookedSixburgerMVi = CreateMV("toBecookedSixBurger", 19);
	/* foodToBeCookedData.threeBurger */
	toBeCookedThreeburgerMVi = CreateMV("toBecookedThreeBurger", 21);
	/* foodToBeCookedData.vegBurger */
	toBeCookedVegburgerMVi = CreateMV("toBecookedVegBurger", 19);
	/* foodToBeCookedData.fries */
	toBeCookedFriesMVi = CreateMV("toBecookedFriesBurger", 21);
	
	
	for(index = 1; index <= OT_COUNT; index++){
		/* orderTakerStatus[index] */
		sprintf(ordertakerstatusMV,"ordertakerstatus[%d]", index);
		ordertakerstatusMVi[index] = CreateMV(ordertakerstatusMV, 19);
	}
	for(index = 1; index <= CUST_COUNT; index++){
		/* custData[index].bagged */
		sprintf(baggedMV, "baggedincustDB[%d]", index);
		baggedincustDBMVi[index] = CreateMV(baggedMV, 18);
		/* custData[index].dineType */
		sprintf(dineTypeMV, "dineTypeincustDB[%d]", index);
		dineTypeincustDBMVi[index] = CreateMV(dineTypeMV, 20);
		/* custData[index].dilivered */
		sprintf(deliveredMV, "deliveredincustDB[%d]", index);
		deliveredincustDBMVi[index] = CreateMV(deliveredMV, 21);
		/* baggedlist[index] */
		sprintf(baggedMV, "baggedlist[%d]" index);
		baggedListMVi[index] = CreateMV(baggedMV, 14);
		/* custData[index].myOT */
		sprintf(myOTMV, "myOTincustDB[%d]", index);
		myOTMVi[index] = CreateMV(myOTMV, 16);
		/* custData[index].ordered */
		sprintf(orderedMV, "orderedincustDB[%d]", index);
		orderedincustDBMVi[index] = CreateMV(orderedMV, 16);
		/* custData[index].sixBurger/threeBurger/etc. */
		sprintf(sixBurgerMV, "sixBurgerincustDB[%d]", index);
		sixBurgerincustDBMVi[index] = CreateMV(sixBurgerMV, 21);
		sprintf(threeBurgerMV, "threeBurgerincustDB[%d]", index);
		threeBurgerincustDBMVi[index] = CreateMV(threeBurgerMV, 23);
		sprintf(vegBurgerMV, "vegBurgerincustDB[%d]", index);
		vegBurgerincustDBMVi[index] = CreateMV(vegBurgerMV, 21);
		sprintf(friesMV, "friesincustDB[%d]", index);
		friesincustDBMVi[index] = CreateMV(friesMV, 17);
		sprintf(sodaMV, "sodaincustDB[%d]", index);
		sodaincustDBMVi[index] = CreateMV(sodaMV, 16);
		/* custData[Index].tokenNo/tableNo */
		sprintf(tokenNoMV, "tokenNoincustDB[%d]", index);
		tokenNoincustDBMVi[index] = CreateMV(tokenNoMV, 19);
		sprintf(tableNoMV, "tableNoincustDB[%d]", index);
		tableNoincustDBMVi[index] = CreateMV(tableNoMV, 19);
	}
	/* tables[index] */
	for(index = 1; index <= TABLE_COUNT; index++){ 
		sprintf(tablesMV, "tables[%d]" index);
		tablesMVi[index] = CreateMV(tablesMV, 9);
	}

}

void Waiter(){
	
	int index = 0, indexj = 0;
	int tableNo = 0;
	int baggedListNotEmpty = 0;
	int custHasNoTable = 0;
	int myIndex = 0;

	int tempV = 0; 
	int nextOrderTakerIndexMVi = 0;
	int nextCustomerIndexMVi = 0;
	int custServed = 0; 
	int custServedMVi = 0;
	int custLineLength = 0;
	int custLineLengthMVi = 0;
	int managerLineLengthMVi = 0;
	int ordertakerstatusMVi[OT_COUNT] = 0;
	int ordertakerstatus[OT_COUNT] = 0;
	int tableAvailableMVi = 0;
	int foodToBag = 0; 
	int foodToBagMVi = 0;
	int baggedincustDBMVi[CUST_COUNT] = 0;
	int dineTypeincustDBMVi[CUST_COUNT] = 0;
	int deliveredincustDBMVi[CUST_COUNT] = 0;
	int baggedList[CUST_COUNT] = 0;
	int baggedListMVi[CUST_COUNT] = 0;
	int myOTMVi[CUST_COUNT] = 0;
	int orderedincustDBMVi[CUST_COUNT] = 0;
	int sixBurgerincustDBMVi[CUST_COUNT] ;
	int threeBurgerincustDBMVi[CUST_COUNT] ;
	int vegBurgerincustDBMVi[CUST_COUNT] ;
	int friesincustDBMVi[CUST_COUNT] ;
	int sodaincustDBMVi[CUST_COUNT] ; 
	int tokenNoincustDBMVi[CUST_COUNT];
	int tableNoincustDBMVi[CUST_COUNT];
	int tablesMVi[TABLE_COUNT];
	int readySixBurgerMVi;
	int readyThreeBurgerMVi;
	int readyVegBurgerMVi;
	int readyFriesMVi;
	int toBeCookedSixburgerMVi;
	int toBeCookedThreeburgerMVi;
	int toBeCookedVegburgerMVi;
	int toBeCookedFriesMVi;	
	int nextTokenNumberMVi;
	int moneyAtRestaurantMVi;
	
	CreateAllMV();
	
	/* Get the Index for this Cook before starting the job */
	Acquire(nextWaiterIndexLock);
	myIndex = GetMV(nextWaiterIndexMVi);
	tempV = GetMV(nextWaiterIndexMVi) + 1;
	SetMV(GetMV(nextWaiterIndexMVi), tempV);
	Release(nextWaiterIndexLock);

	while(1){
		index = 0;
		tableNo = 0;
		baggedListNotEmpty = 0;
		/* Acquire Lock to check if any orders are bagged*/
		Acquire(foodBaggedListLock);
		/* check if token numbers of bagged food are present in bagged list*/
		for(index = 1; index <= CUST_COUNT; index++){
			if(GetMV(baggedListMVi[index]) != 0){
				baggedListNotEmpty =GetMV(baggedListMVi[index]);
				SetMV(GetMV(baggedListMVi[index]), 0);
				break;
			}
		}
		Release(foodBaggedListLock);
	
		if(baggedListNotEmpty != 0){
			int firstTokenNo = 0;	
			/* remove first token number from the bagged list */
			/* to serve it for the customer waiting for it*/
			firstTokenNo = baggedListNotEmpty;
			/* Acquire tableDataLock to obtain the table number of the */
			/* Eat-in seated customer */			
			Acquire(tablesDataLock);
	
			/* Determine the table number of the Eat-in Customer*/
			for(index = 1; index <= TABLE_COUNT; index++){
				/* Find the table number using token number removed from */
				/* bagged list*/
				if(GetMV(tablesMVi[index]) == firstTokenNo){
					tableNo = index;
				    break;
				}
			}
			Release(tablesDataLock);
			
			/* Search for a particular token number with all customers */
			for(index = 1; index <= CUST_COUNT; index++){
				custHasNoTable = 0;
				/* If token number of customer matches set the delivered which*/
				/* indicates the food has been served.*/
				
				Acquire(customerDataLock);
				if(GetMV(tokenNoincustDBMVi[index]) == firstTokenNo){
					/* check if the customer is seated */
					if(GetMV(tableNoincustDBMVi[index]) != 0){ 
					
						/* OG */
						Print_2Arg("Waiter %d validates the token number for Customer %d and serves the food\n$", myIndex, index);
						
						
						if(GetMV(baggedincustDBMVi[index]) == 1)
							SetMV(deliveredincustDBMVi[index], 1);
							
						Release(customerDataLock);
						/* OG */
						Print_2Arg("Waiter %d serves food to Customer %d\n$", myIndex, index);
						/* Notifying the Eatin seated customer that the order */
						/* has been delivered*/
						Acquire(eatInFoodWaitingLock);
						/* Broadcasting the notification about the order*/
						/* delivered. This signal will be processed only by*/
						/* that customer whose order was bagged, others*/
						/* will go back to wait again.*/
						Broadcast(eatInFoodWaitingCV, eatInFoodWaitingLock);
						Release(eatInFoodWaitingLock);
					}
					/* else if the customer has not yet got his table to sit*/
					/* then put back the bagged order into the List*/
					else{ 
						Release(customerDataLock);
						Acquire(foodBaggedListLock);
						for(indexj = 1; indexj <= CUST_COUNT; indexj++){
							if(GetMV(baggedListMVi[indexj]) == 0){
								SetMV(baggedListMVi[indexj], firstTokenNo);
								custHasNoTable = 1;
								break;
							
							}
						}
						Release(foodBaggedListLock);
					}	
					if(custHasNoTable == 0)
						break;
				}
				else
					Release(customerDataLock);
			}
		}
		if((baggedListNotEmpty == 0) || (custHasNoTable == 1)){
			/* Waiter Acquires Lock and Goes on wait (break) till he receives */
			/* a wake up signal from the manager */
			Acquire(waiterSleepLock);
			/* OG */
			Print_1Arg("Waiter %d is going on break\n$", myIndex);
			Wait(waiterSleepCV,waiterSleepLock);
			/* Received a signal from the manager, waiter starts with his job */
			Release(waiterSleepLock);
			/* Check if all the Customers are serviced */
			Acquire(custServedLock);
			if(GetMV(custServedMVi) == CUST_COUNT){			
				Release(custServedLock);
				/* @ */
				/* Print_1Arg("Waiter %d calling E---X---I---T\n$", myIndex); */
				Exit(0);
			}
			Release(custServedLock);
			/* OG */
			Print_1Arg("Waiter %d returned from break\n$", myIndex);
		}

	
	}
	
}	





