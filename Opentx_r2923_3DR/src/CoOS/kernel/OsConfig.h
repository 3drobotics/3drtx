/**
 *******************************************************************************
 * @file       OsConfig.h
 * @version   V1.1.4    
 * @date      2011.04.20
 * @brief      This file use by user to configuration CooCox CoOS.
 * @note       Ensure you have knew every item before modify this file. 
 *******************************************************************************
 * @copy
 *
 * INTERNAL FILE,DON'T PUBLIC.
 * 
 * <h2><center>&copy; COPYRIGHT 2009 CooCox </center></h2>
 *******************************************************************************
 */ 


#ifndef  _CONFIG_H
#define  _CONFIG_H


/*!< 
Defines chip type,cortex-m3(1),cortex-m0(2)      
*/
#define CFG_CHIP_TYPE           (1)

/*!< 
Defines the lowest priority that be assigned.       
*/
#define CFG_LOWEST_PRIO         (64)

/*!< 
Max number of tasks that can be running.		     
*/			
#define CFG_MAX_USER_TASKS      (5)

/*!< 
Idle task stack size(word).		                         
*/	
#define CFG_IDLE_STACK_SIZE     (25)

/*!< 
System frequency (Hz).	                 	         
*/    
#if defined(PCBTARANIS)
#define CFG_CPU_FREQ            (60000000)
#else
#define CFG_CPU_FREQ            (36000000)  // TODO check if really correct for sky9x?
#endif

/*!< 
systick frequency (Hz).	                         
*/
#define CFG_SYSTICK_FREQ        (500)

/*!< 
max systerm api call num in ISR.	                         
*/
#define CFG_MAX_SERVICE_REQUEST (5)

/*!< 
Enable(1) or disable(0) order list schedule.
If disable(0),CoOS use Binary-Scheduling Algorithm. 
*/
#if (CFG_MAX_USER_TASKS) <15
#define CFG_ORDER_LIST_SCHEDULE_EN  (1)
#else 
#define CFG_ORDER_LIST_SCHEDULE_EN  (0)
#endif	


/*!< 
Enable(1) or disable(0) Round-Robin Task switching. 
*/
#define CFG_ROBIN_EN            (1)         

/*!< 
Default slice of task.   	                          
*/
#if	CFG_ROBIN_EN > 0
#define CFG_TIME_SLICE          (10)	  		
#endif


/*----------------------- Schedule model Config -----------------------------*/
/*!< 
Enable(1) or disable(0) all waiting function.
Include sem,mailbox,queue,flag,mutex,delay modules.	
If CFG_TASK_WAITTING_EN=0,all these modules are disable.	      
*/
#define CFG_TASK_WAITTING_EN     (1)

/*!< 
Dynamic task scheduling(1) or Static Task Scheduling(0) model.
If in Static Task Scheduling model(0),cannot creat task and change task priority
after coocox os start running. In Dynamic Task Scheduling model(1), all these can.
When task terminated, if in Static Task Scheduling model(0), 
CoOS do not recovered task resources, and you can activate it again.
But in Dynamic Task Scheduling model(1),task resources will be recovered.
If in Static Task Scheduling model(0),mutex module can not be used, as this model don't
support to change task priority while CoOS running. 
*/
#define CFG_TASK_SCHEDULE_EN     (1)


/*---------------------- Task Management Config -----------------------------*/
/*!< 
Enable(1) or disable(0) CoSetPriority() API.		      
*/
#if CFG_TASK_SCHEDULE_EN >0
#define CFG_PRIORITY_SET_EN       (1)	
#endif

/*!< 
Enable(1) or disable(0) CoAwakeTask() and CoSuspendTask() API.		      
*/
#define CFG_TASK_SUSPEND_EN       (0)


/*---------------------- Debug Management Config ----------------------------*/
/*!< 
Enable(1) or disable(0) parameter checkout .		  
*/
#define CFG_PAR_CHECKOUT_EN     (0)	

/*!< 
Enable(1) or disable(0) stack overflow checkout .  	  
*/		
#define CFG_STK_CHECKOUT_EN     (0)		



/*---------------------- Memory Management Config ----------------------------*/
/*!< 
Enable(1) or disable(0) memory management.	      
*/
#define CFG_MM_EN               (0)   

/*!< 
Max number of memory.(must be less than 32).      
*/ 
#if CFG_MM_EN >0
#define CFG_MAX_MM              (2)
#endif 



/*-------------------- Kernel heap Management Config -------------------------*/
/*!< 
Enable(1) or disable(0) kernel heap management.	      
*/
#define CFG_KHEAP_EN            (0)  		

/*!< 
Kernel heap size(word).      
*/ 
#if CFG_KHEAP_EN >0
#define KHEAP_SIZE              (50)
#endif   


		
/*---------------------- Time Management Config -----------------------------*/
/*!< 
Enable(1) or disable(0) TimeDelay() API.		      
*/
#if CFG_TASK_WAITTING_EN >0
#define CFG_TIME_DELAY_EN       (0)	
#endif


/*---------------------- Timer Management Config ----------------------------*/
/*!< 
Enable(1) or disable(0) timer management.		      
*/
#define CFG_TMR_EN              (1)		

/*!< 
Specify max number timer.(must be less than 32)      
*/	
#if CFG_TMR_EN >0
#define CFG_MAX_TMR             (2)			
#endif


/*---------------------- Event Management Config ----------------------------*/
/*!< 
Enable(1) or disable(0) events management,			 
events including semaphore,mailbox,queue.             
*/
#if CFG_TASK_WAITTING_EN > 0
#define  CFG_EVENT_EN           (1) 
#endif
	   	
#if CFG_EVENT_EN > 0
/*!< 
Event sort type.(1)FIFO (2)PRI (3)FIFO+PRI           
*/
#define CFG_EVENT_SORT          (3)		

/*!< 
Max number of event.(must be less than 255) 	      
Event = semaphore + mailbox + queue;			      
*/
#define CFG_MAX_EVENT           (10)

/*!< 
Enable(1) or disable(0) semaphore management.	      
*/
#define CFG_SEM_EN              (0)	

/*!< 
Enable(1) or disable(0) mailbox management.	      
*/		
#define CFG_MAILBOX_EN          (0)	

/*!< 
Enable(1) or disable(0) queue management.		      
*/		
#define CFG_QUEUE_EN            (0)	

/*!< 
Max number of queue.(less than CFG_MAX_EVENT).       
*/
#if	CFG_QUEUE_EN >0	
#define CFG_MAX_QUEUE           (2)
#endif   // CFG_QUEUE_EN
	
#endif   // CFG_EVENT_EN
	


/*----------------------- Flag Management Config ----------------------------*/
/*!< 
Enable(1) or disable(0) flag management.		     
Max number of flag is 32.					    	  
*/
#if CFG_TASK_WAITTING_EN > 0
#define  CFG_FLAG_EN            (1)
#endif		


/*---------------------- Mutex Management Config ----------------------------*/
/*!< 
Enable(1) or disable(0) mutex management.	      
*/
#if CFG_TASK_WAITTING_EN > 0
#if CFG_TASK_SCHEDULE_EN > 0
#define  CFG_MUTEX_EN           (1)
#endif
#endif

 
/*!< 
Max number of mutex.(must be less than 255).      
*/ 
#if CFG_MUTEX_EN >0
#define CFG_MAX_MUTEX           (10)			
#endif

/*---------------------- Utility Management Config --------------------------*/
/*!< 
Enable(1) or disable(0) utility management.    	  
*/
#define CFG_UTILITY_EN          (0)      
   
#if CFG_UTILITY_EN >0

/*!< 
Enable(1) or disable(0) TickToTime() utility	
*/
#define	CFG_TICK_TO_TIME_EN     (1)		
/*!< 
Enable(1) or disable(0) TimeToTick() utility	
*/	
#define	CFG_TIME_TO_TICK_EN     (1)		
#endif


#endif	 // _CONFIG_H
