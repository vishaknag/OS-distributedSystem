#include "syscall.h"

void main()
{
	
	typedef struct{
			int sixBurger;   /* Costs 6$	/* value = 0 -> not ordered */
			int threeBurger; /* Costs 3$ 	   value = 1 -> ordered */
			int vegBurger;    /* Costs 8$	   value = 2 -> item is reserved */
			int fries;        /* Costs 2$	*/
			int soda;         /* Costs 1$	*/
			int dineType;    /* Type of service the customer has opted for */
							  /* - Eat-in = 0 */
							  /* - To-go  = 1 */   
			int ordered;		  /* set if he already take the order */
			
			int myOT;		  /* index of the OrderTaker servicing the customer */
			int tokenNo;	  /* Unique number which identifies the order  */
							  /* of the current customer */
			int tableNo;	  /* where the eat-in customer is seated	 */
			int bagged;		  /* set if order is bagged by Order Taker	 */
			int delivered;	  /* set if the order is bagged and delivered */
		}custDB; 	
	custDB custData[30];
	
	int OT_COUNT = 2;
	int CUST_COUNT = 2;
	int OT_WAIT = 2;
	int OT_FREE = 0;
	int OT_BUSY = 1;
	int TABLE_COUNT = 20;
	
	
	
	int index = 0; 
	int internalOT = 0;
	int myIndex = 0;
	int nextCustomerIndexMVi = 0;
	int tempV = 0;
	int ordertakerstatusMVi[OT_COUNT];
	int ordertakerstatus[OT_COUNT];
	int custLineLengthMVi = 0 ;
	int custServedMVi = 0;
	int myOTMVi[CUST_COUNT];
	int sixBurgerincustDBMVi[CUST_COUNT];
	int threeBurgerincustDBMVi[CUST_COUNT];
	int vegBurgerincustDBMVi[CUST_COUNT];
	int friesincustDBMVi[CUST_COUNT];
	int sodaincustDBMVi[CUST_COUNT];
	int dineTypeincustDBMVi[CUST_COUNT];
	int deliveredincustDBMVi[CUST_COUNT];
	int tablesMVi[TABLE_COUNT];
	int tables[TABLE_COUNT];
	int managerLineLengthMVi = 0;
	int tableAvailableMVi = 0;
	int tableAvailable = 0;
	int tokenNoincustDBMVi[CUST_COUNT];
	int tableNoincustDBMVi[CUST_COUNT];
	
	
	
		
/*----------------added varaiables ----------------*/	
	int nextCustomerIndexLock = 0;
	int custLineLock = 0;   
	int customerDataLock = 0;
	int custLineCV = 0;
	int custServedLock = 0;
	int waitToGoLock;
	int toGoCV = 0;
	int managerLock = 0;
	int managerCV = 0;
	int tablesDataLock = 0;
	int eatInFoodWaitingLock = 0;
	int eatInFoodWaitingCV = 0;
	int eatInWaitingLock = 0;
	int eatInWaitingCV = 0;
	int orderTakerStatus[25];
	int orderTakerLock[25];
	int orderTakerCV[25];
/*------------------------------------------------*/
	
	/*--------------------Locks----------------------*/
	waitToGoLock = CreateLock("waitToGoLock", 12, 0);
	Print_1Arg("waitToGoLock =%d\n\n\n\n\n", waitToGoLock);
	managerLock = CreateLock("managerLock", 11, 0);
	tablesDataLock = CreateLock("tablesDataLock", 14, 0);
	
	eatInFoodWaitingLock = CreateLock("eatInFoodWaitingLock", 20, 0);
	eatInWaitingLock = CreateLock("eatInWaitingLock", 16, 0);
	custLineLock = CreateLock("custLineLock", 12, 0);
	nextCustomerIndexLock = CreateLock("nextCustomerIndexLock", 21, 0);
	customerDataLock = CreateLock("customerDataLock", 16, 0);
	custServedLock = CreateLock("custServedLock", 14, 0);
	
	/* Create OT_COUNT number of locks, one Lock for each Ordertaker	*/
	for(index = 0; index < OT_COUNT; index++)
		orderTakerLock[index] = CreateLock("orderTakerLock", 14, index);
	/*-----------------CV's -----------------------*/
	custLineCV = CreateCV("custLineCV", 10, 0);
	for(index = 0; index < OT_COUNT; index++)
		orderTakerCV[index] = CreateCV("orderTakerCV", 12, index);
	toGoCV = CreateCV("toGoCV", 6, 0); 
	managerCV = CreateCV("managerCV", 9, 0);
	eatInFoodWaitingCV = CreateCV("eatInFoodWaitingCV", 18, 0);
	eatInWaitingCV = CreateCV("eatInWaitingCV", 14, 0);
	
	
	/* nextCustomerIndex */
	nextCustomerIndexMVi = CreateMV("nextCustomerIndex", 17, 0);
	/* custLineLength */
	custLineLengthMVi = CreateMV("custLineLength", 14, 0);
	/* custServed */
	custServedMVi = CreateMV("custServed", 10, 0);
	/* managerLineLength */
	managerLineLengthMVi = CreateMV("managerLineLength", 17, 0);
	/* tableAvailable */
	tableAvailableMVi = CreateMV("tableAvailable", 14, 0);
	
	for(index = 0; index < OT_COUNT; index++)
	{	
		ordertakerstatusMVi[index] = CreateMV("ordertakerstatusMV", 18, index);
	}
	
	
	for(index = 0; index < CUST_COUNT; index++)
	{
		
		myOTMVi[index] = CreateMV("myOTMV", 6, index);
		sixBurgerincustDBMVi[index] = CreateMV("sixBurgerMV", 11, index);
		threeBurgerincustDBMVi[index] = CreateMV("threeBurgerMV", 13, index);
		vegBurgerincustDBMVi[index] = CreateMV("vegBurgerMV", 11, index);
		friesincustDBMVi[index] = CreateMV("friesMV", 7, index);
		sodaincustDBMVi[index] = CreateMV("sodaMV", 6, index);
		dineTypeincustDBMVi[index] = CreateMV("dineTypeMV", 10, index);	
		deliveredincustDBMVi[index] = CreateMV("deliveredMV", 11, index);
		tableNoincustDBMVi[index] = CreateMV("tableNoMV", 9, index);
		tokenNoincustDBMVi[index] = CreateMV("tokenNoMV", 9, index);
	}
	for(index = 0; index < TABLE_COUNT; index++)
	{
		tablesMVi[index] = CreateMV("tablesMV", 9, index);
	}
		/* Get the Index for this Customer before starting the order*/
	Acquire(nextCustomerIndexLock);	
	myIndex = GetMV(nextCustomerIndexMVi);
	tempV = myIndex + 1;
	SetMV(nextCustomerIndexMVi, tempV);
	
	Release(nextCustomerIndexLock);
	/* Acquire this LOCK to become the NEXT eligible customer */	
	/* Check if any Order Taker is FREE */
	/* - if any then make him as the Order Taker for the current customer */
	/* - Make that Order Taker status as BUSY */
	
	Print_Stmt(" in code\n");
	
	for(index = 0; index < OT_COUNT; index++)
	{
		Acquire(custLineLock);
		
		ordertakerstatus[index] = GetMV(ordertakerstatusMVi[index]);
		
		if(orderTakerStatus[index] == OT_FREE){	
			orderTakerStatus[index] = OT_BUSY;
			SetMV(ordertakerstatusMVi[index], orderTakerStatus[index]);
			Release(custLineLock);
			Acquire(customerDataLock);
			custData[myIndex].myOT = index;
			SetMV(myOTMVi[myIndex], custData[myIndex].myOT);
			Release(customerDataLock);
			break;
		}
		Release(custLineLock);
	}
	/*If no Order Takers are free */
	/* - increment the linelength monitor variable */
	/* - then wait in the customer waiting line */
	Acquire(customerDataLock);
	if(custData[myIndex].myOT == 0){
		
		Release(customerDataLock);
		Acquire(custLineLock);
		

		tempV = GetMV(custLineLengthMVi);	
		
		tempV++;
		SetMV(custLineLengthMVi, tempV);
		Print_Stmt("\n\n\n\going to wait\n\n\n\n");
		Wait(custLineCV, custLineLock);
		Release(custLineLock);
	}else	
		Release(customerDataLock);
		
	/* Customer is here because he received a signal from the Order Taker */
	/* - customer has also acquired the custLineLock */

	/* Check for the Order Taker who is WAITING */
	/* - make him as the Order Taker for the current customer */
	/* - Make that Order Taker status as BUSY */
	Acquire(customerDataLock);
	if(custData[myIndex].myOT == 0){
		Release(customerDataLock);
		for(index = 0; index < OT_COUNT; index++){ 
			Acquire(custLineLock);
			ordertakerstatus[index] = GetMV(ordertakerstatusMVi[index]);
			if(orderTakerStatus[index] == OT_WAIT){	
				orderTakerStatus[index] = OT_BUSY;
				SetMV(ordertakerstatusMVi[index], orderTakerStatus[index]);
				Release(custLineLock);
				Acquire(customerDataLock);
				custData[myIndex].myOT = index;
				SetMV(myOTMVi[myIndex], custData[myIndex].myOT); 			
				Release(customerDataLock);	
				break;
			}else
				Release(custLineLock);
		}
	}else	
		Release(customerDataLock);	

	internalOT = custData[myIndex].myOT;
	Acquire(orderTakerLock[internalOT]);
	/* Send a signal to the Order Taker which indicates that the customer */
	/* is ready to give the order */
	Signal(orderTakerCV[internalOT], orderTakerLock[internalOT]);
    /* Customer goes on wait to receive a signal from the Order Taker */
	/* which indicates Order Taker is ready to take the order */
	Wait(orderTakerCV[internalOT], orderTakerLock[internalOT]);
	Release(orderTakerLock[internalOT]);
	/* Customer received a signal from the Order Taker to place an order */
	/* Order is randomly generated and is stored in the customer database */
	Print_2Arg("Customer %d is giving order to OrderTaker %d\n$", myIndex, internalOT);
	Acquire(customerDataLock);
		
	custData[myIndex].sixBurger = GetMV(sixBurgerincustDBMVi[myIndex]);
	custData[myIndex].threeBurger = GetMV(threeBurgerincustDBMVi[myIndex]);
	custData[myIndex].vegBurger = GetMV(vegBurgerincustDBMVi[myIndex]);
	custData[myIndex].fries = GetMV(friesincustDBMVi[myIndex]);
	custData[myIndex].soda = GetMV(sodaincustDBMVi[myIndex]);
	custData[myIndex].dineType = GetMV(dineTypeincustDBMVi[myIndex]);	
	
	
	if(custData[myIndex].sixBurger == 1){
		Print_1Arg("Customer %d is ordering 6-dollar burger\n$", myIndex);
	}else{
		Print_1Arg("Customer %d is not ordering 6-dollar burger\n$", myIndex);
	}
	if(custData[myIndex].threeBurger == 1){
		Print_1Arg("Customer %d is ordering 3-dollar burger\n$", myIndex);
	}else{
		Print_1Arg("Customer %d is not ordering 3-dollar burger\n$", myIndex);
	}
	if(custData[myIndex].vegBurger == 1){
		Print_1Arg("Customer %d is ordering veggie burger\n$", myIndex);
	}else{
		Print_1Arg("Customer %d is not ordering veggie burger\n$", myIndex);
	}
	if(custData[myIndex].fries == 1){
		Print_1Arg("Customer %d is ordering french fries\n$", myIndex);
	}else{
		Print_1Arg("Customer %d is ordering french fries\n$", myIndex);
	}
	if(custData[myIndex].soda == 1){
		Print_1Arg("Customer %d is ordering soda\n$", myIndex);
	}else{
		Print_1Arg("Customer %d is not ordering soda\n$", myIndex);
	}
	if(custData[myIndex].dineType == 1){
		Print_1Arg("Customer %d chooses to to-go the food\n$", myIndex);
	}else{
		Print_1Arg("Customer %d chooses to eat-in the food\n$", myIndex);
	}
	Release(customerDataLock);
	Acquire(orderTakerLock[internalOT]);
	Signal(orderTakerCV[internalOT],orderTakerLock[internalOT]);
	/* wait for the Order Taker to reply once he checks the food availability */
	Wait(orderTakerCV[internalOT],orderTakerLock[internalOT]);
	
	/* Received a signal from Order Taker which indicates that the order is */
	/* processed and its time to pay money */
	
	/* Send a signal to the Order Taker which indicates that the customer */
	/* has payed the bill amount */ 
	Signal(orderTakerCV[internalOT],orderTakerLock[internalOT]);
	/* Wait for the Order Taker to acknowledge the payment being done */ 
	/* successfully */
	Wait(orderTakerCV[internalOT], orderTakerLock[internalOT]);
	Release(orderTakerLock[internalOT]);
	/* Received a signal from the Order Taker to indicate that the payment */
	/* was completed and the customer can move to the next stage */ 

	/* If to-go then check if the order is bagged right away */
	/* else go and wait for a broadcast of the tokenNo */
	
	if(custData[myIndex].dineType == 1)
	{
		/* if to-go and if the order is delivered then the customer takes the */
		/* bag and just leaves the restaurant */
		/* release the Order Taker Lock */
		Acquire(customerDataLock);
		
		
		custData[myIndex].delivered = GetMV(deliveredincustDBMVi[myIndex]);
		if(custData[myIndex].delivered == 1)
		{
			Release(customerDataLock);	
			/* OG */
			Print_2Arg("Customer %d receives food from the OrderTaker %d\n$",myIndex, internalOT);
			/* Acquire the Lock to update the custer count served the food */
			Acquire(custServedLock);
			
			tempV = GetMV(custServedMVi);
			tempV ++;
			SetMV(custServedMVi, tempV);
			
			/* @ */
			/* Print_2Arg("\n\nCUSTOMER %d SERVICED IS %d\n\n$", myIndex, custServed); */
			Release(custServedLock);
			/* Print_1Arg("To Go Customer %d calling E---X---I---T\n$", myIndex); */
			Exit(0);
	
			/* if to-go and if the order is not ready then customer has to wait */
			/* for a broadcast signal from the Order Taker when the order is bagged */
		
			/* Acquire the Lock which is used to match with To-go waiting */
			/* condition variable waitingLock */
		}
		else
		{
			Release(customerDataLock);	
			/* OG */
			Print_3Arg("Togo Customer %d is given token number %d by the OrderTaker %d\n$", myIndex, custData[myIndex].tokenNo, internalOT);
			Acquire(waitToGoLock);
				
			/* Go on wait to receive the broadcast signal from the Order Taker */
			Wait(toGoCV,waitToGoLock);
			Release(waitToGoLock);

			while(1)
			{
				/* Received a Broadcast signal from one of the Order Taker */
				/* - Check if the broadcasted tokenNo is customer's tokenNo */
				Acquire(customerDataLock);
				if(custData[myIndex].delivered = 1)
				{
					Release(customerDataLock);
					/* Acquire the Lock to update the custer count served the food */
					Acquire(custServedLock);
					
					tempV = GetMV(custServedMVi);
					tempV ++;
					SetMV(custServedMVi, tempV);
					
					/* @ */
					/* Print_2Arg("\n\nCUSTOMER %d SERVICED IS %d\n\n$", myIndex,custServed); */
					Release(custServedLock);
					/* Print_1Arg("Customer %d calling E---X---I---T\n$", myIndex); */
					Exit(0);
					break;
				}else
				{ 
					Release(customerDataLock);
					/* Go on wait to receive the next broadcast signal from the waiter */
					Acquire(waitToGoLock);
					Wait(toGoCV,waitToGoLock);
					Release(waitToGoLock);
				}	
			}
	    }
	}/* if dineType is eat-in */
	else if(custData[myIndex].dineType == 0)
	{
				/*  OG */
		/* Print_3Arg("EatinCustomer %d is given token number %d by the OrderTaker %d\n$", myIndex, custData[myIndex].tokenNo, internalOT); */
		/* Acquire a Lock to add customer onto the queue waiting for */
		/* manager's reply */
		Acquire(managerLock);
		/* Increment the customer waiting count */
					
		tempV = GetMV(managerLineLengthMVi);
		tempV ++;
		SetMV(managerLineLengthMVi, tempV);
					
		/* go on wait till manager signals with table availability */
		Wait(managerCV,managerLock);

		/* Received a signal from manager */
		/* Customer has acquired the manager lock */
		/* Manager replied saying "restaurant is not full" */
		tableAvailable = GetMV(tableAvailableMVi);
		
		if(tableAvailable == 1)
		{		
			/* OG */
			Print_1Arg("Customer %d is informed by the Manager-the restaurant is not full\n$", myIndex);
			
			tableAvailable = 0;
			SetMV(tableAvailableMVi, tableAvailable);
			custData[myIndex].tableNo = GetMV(tableNoincustDBMVi[myIndex]);

			Release(managerLock);			
			for(index = 0; index < TABLE_COUNT; index++)
			{
				Acquire(tablesDataLock);
				
				tables[index] = GetMV(tablesMVi[index]);
				
				if(tables[index] == 0)
				{
					/* make the first table which is free as the customer */
					/* table */
					
					custData[myIndex].tokenNo = GetMV(tokenNoincustDBMVi[myIndex]);
					tables[index] = custData[myIndex].tokenNo;
					SetMV(tablesMVi[index],tables[index]);
					
					Release(tablesDataLock);
					Acquire(customerDataLock);
					
					custData[myIndex].tableNo = index;
					SetMV(tableNoincustDBMVi[myIndex], custData[myIndex].tableNo);
								
					Release(customerDataLock);
					/* @ */
					/* Print_3Arg("table %d is taken by custom %d tokenNo %d\n$", index, myIndex, tables[index]);	 */
					break;
				}else
					Release(tablesDataLock);
			}

			/* if a table is found then go sit and wait for food */
			if(custData[myIndex].tableNo != 0)
			{	
				/* OG	*/
				Print_2Arg("customer %d is seated at table number %d\n$",myIndex, custData[myIndex].tableNo);
					
				/* Before releasing the tablesDataLock Acquire the */
				/* eatInFoodWaitingLock to ensure that this customer is the */ 
				/* next one to join the queue waiting for the food to be bagged */

				/* customer goes on wait to receive a signal from the waiter */
				/* after the tokenNo is validated */
				while(1)
				{
					Acquire(eatInFoodWaitingLock);
					Wait(eatInFoodWaitingCV,eatInFoodWaitingLock);	
					Release(eatInFoodWaitingLock);
		 			/* upon receiving the signal check if order is delivered */
					Acquire(customerDataLock);
					
					custData[myIndex].delivered = GetMV(deliveredincustDBMVi[myIndex]);
					
					if(custData[myIndex].delivered == 1)
					{
						/* if delivered then the customer eats the food and */
						/* leaves the restaurant */
						Release(customerDataLock);
						Acquire(tablesDataLock);			
						tables[custData[myIndex].tableNo] = 0;
						
						SetMV(tablesMVi[custData[myIndex].tableNo],tables[custData[myIndex].tableNo]);
						
						Release(tablesDataLock);
						Acquire(eatInWaitingLock);
						Signal(eatInWaitingCV,eatInWaitingLock);
						Release(eatInWaitingLock);	
						/* Acquire the Lock to update the custer count served the food */
						Acquire(custServedLock);
						
						tempV = GetMV(custServedMVi);
						tempV ++;
						SetMV(custServedMVi, tempV);
						/* @ */
						/* Print_2Arg("\n\nCUSTOMER %d SERVICED IS %d\n\n$", myIndex, custServed); */
						Release(custServedLock);
						/* Print_1Arg("Customer %d calling E---X---I---T\n$", myIndex); */
						Exit(0);	
					}
					Release(customerDataLock);
				}
			}

		}
		else if(tableAvailable == 0)
		{
			Release(managerLock);
			/* OG */
			Print_1Arg("Customer %d is informed by the Manager-the restaurant is full\n$", myIndex);
			/* if restaurant is full and no table is available where the */
			/* customer can sit */
				
			/* Acquire the eat-in table waiting lock before releasing the */
			/* tablesDataLock so that customer wont get context switched */
			/* and he can be the next person to join the waiting queue */
				
			/* Release the tables Data lock	 */
			
			Acquire(eatInWaitingLock);	
			/* OG */
			Print_1Arg("customer %d is waiting to sit on the table\n$", myIndex);
				
			/* Customer goes on wait till he receives a signal from */
			/* a seated customer who received his bag and is leaving */
			/* the restaurant */
			Wait(eatInWaitingCV,eatInWaitingLock);
			Release(eatInWaitingLock);
			/* Received a signal from one of the customer leaving */
			/* Acquire the Lock on the tables data to make the */
			/* freed table number as the current customer table */
			Acquire(tablesDataLock);	
		
			for(index = 0; index < TABLE_COUNT; index++)
			{
				
				tables[index] = GetMV(tablesMVi[index]);
				
				if(tables[index] == 0)
				{
					/* make the first table which is free as the customer */
					/* table */
					
					custData[myIndex].tokenNo = GetMV(tokenNoincustDBMVi[myIndex]);
					tables[index] = custData[myIndex].tokenNo;
					SetMV(tablesMVi[index],tables[index]);
					
					Release(tablesDataLock);
					Acquire(customerDataLock);
					
					custData[myIndex].tableNo = index;
					SetMV(tableNoincustDBMVi[myIndex], custData[myIndex].tableNo);
					
					Release(customerDataLock);
					Acquire(tablesDataLock);
					break;
				}	
			}
			/* Release the tables data lock */
			Release(tablesDataLock);
			Acquire(customerDataLock);
	
			if(custData[myIndex].tableNo != 0)
			{
				Release(customerDataLock);
		
				/* Before releasing the tablesDataLock Acquire the */
				/* eatInFoodWaitingLock to ensure that this customer is the */
				/* next one to join the queue waiting for the food to be bagged */
				Acquire(eatInFoodWaitingLock);
				/* customer goes on wait to receive a signal from the waiter */
				/* after the tokenNo is validated */	
				/* OG */
				Print_1Arg("Customer %d is waiting for the waiter to serve the food\n$",myIndex);
		
				Wait(eatInFoodWaitingCV,eatInFoodWaitingLock);
					/*potential problem	*/
				/* upon receiving the signal check if order is delivered */
				custData[myIndex].delivered = GetMV(deliveredincustDBMVi[myIndex]);
				while(custData[myIndex].delivered != 1)
				{				
					/* else Go Back to wait */
					Wait(eatInFoodWaitingCV,eatInFoodWaitingLock);
				}
				Release(eatInFoodWaitingLock);
				/* OG */
				Print_1Arg("Customer %d is served by waiter\n$", myIndex);
				/* if delivered then the customer eats the food and */
				/* leaves the restaurant */
				Print_2Arg("Customer %d is leaving the restaurant after OrderTaker %d packed the food\n$",myIndex, internalOT);						
				Acquire(tablesDataLock);			
				
				tables[custData[myIndex].tableNo] = 0;
				SetMV(tablesMVi[index], tables[custData[myIndex].tableNo]);
				
				Release(tablesDataLock);
				Acquire(eatInWaitingLock);		
				Signal(eatInWaitingCV,eatInWaitingLock);		
				Release(eatInWaitingLock);
				/* OG */	
				Print_1Arg("EAT-IN  Customer %d is leaving the restaurant after having food\n$",myIndex);				 
				/* Acquire the Lock to update the custer count served the food	*/	
				Acquire(custServedLock);

				tempV = GetMV(custServedMVi);
				tempV ++; 
				SetMV(custServedMVi, tempV);
		
				/* @ */
				/* Print_2Arg("\n\nCUSTOMER %d SERVICED IS %d\n\n$", myIndex, custServed);		 */
				Release(custServedLock);	
				/* Print_1Arg("Customer %d calling E---X---I---T\n$", myIndex);	 */
				Exit(0);
			}
			else
				Release(customerDataLock);
		}
	}	

}
