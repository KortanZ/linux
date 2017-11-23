
#include <ql_oe.h>

void timer_thread(union sigval v)
{
	printf("timer_thread function! %d\n", v.sival_int);
}


int main(int argc, char *argv[])
{
	// XXX int timer_create(clockid_t clockid, struct sigevent *evp, timer_t *timerid);
	// clockid --- CLOCK_REALTIME,CLOCK_MONOTONIC��CLOCK_PROCESS_CPUTIME_ID,CLOCK_THREAD_CPUTIME_ID
	// evp -- ��Ż���ֵ�ĵ�ַ,�ṹ��Ա˵���˶�ʱ�����ڵ�֪ͨ��ʽ�ʹ���ʽ��
	// timerid--��ʱ����ʶ��
	timer_t timerid;
	struct sigevent evp;
	int iRet;
	
	//1. Create 1st timer
	{
		memset(&evp, 0, sizeof(struct sigevent));
	
		evp.sigev_value.sival_int = 111;	// The timer id that developer specify. it can be passed into callback
		evp.sigev_notify = SIGEV_THREAD;	// The thread notifying way -- dispatch a new thread.
		evp.sigev_notify_function = timer_thread;	// The thread address
		
		iRet = 	timer_create(CLOCK_REALTIME, &evp, &timerid);
		printf("< timer_create(%d,..)=%d, timer id=%d >\n", CLOCK_REALTIME, iRet, *((unsigned int*)(&timerid)));
		if (iRet == -1)
		{
			perror("fail to timer_create");
			exit(-1);
		}
	
		// XXX int timer_settime(timer_t timerid, int flags, const struct itimerspec *new_value,struct itimerspec *old_value);
		// timerid -- timer id.
		// flags -- 0, relative time; 1, absolute time
		// new_value -- ��ʱ�����³�ʼֵ�ͼ�����������it
		// old_value--ȡֵͨ��Ϊ0�������ĸ�������ΪNULL,����ΪNULL���򷵻ض�ʱ����ǰһ��ֵ
		
		//��һ�μ��it.it_value��ô��,�Ժ�ÿ�ζ���it.it_interval��ô��,����˵it.it_value��0��ʱ���װ��it.it_interval��ֵ
		struct itimerspec it;
		it.it_interval.tv_sec = 0;
		it.it_interval.tv_nsec = 500000000;
		it.it_value.tv_sec = 3;
		it.it_value.tv_nsec = 0;
	
		if (timer_settime(timerid, 0, &it, NULL) == -1)
		{
			perror("fail to timer_settime");
			exit(-1);
		}
	}
	
	//2. Create 2nd timer
	{
		memset(&evp, 0, sizeof(struct sigevent));
	
		evp.sigev_value.sival_int = 112;	// The timer id that developer specify. it can be passed into callback
		evp.sigev_notify = SIGEV_THREAD;	// The thread notifying way -- dispatch a new thread.
		evp.sigev_notify_function = timer_thread;	// The thread address
		
		iRet = 	timer_create(CLOCK_REALTIME, &evp, &timerid);
		printf("< timer_create(%d,..)=%d, timer id=%d >\n", CLOCK_REALTIME, iRet, *((unsigned int*)(&timerid)));
		if (iRet == -1)
		{
			perror("fail to timer_create");
			exit(-1);
		}
	
		// XXX int timer_settime(timer_t timerid, int flags, const struct itimerspec *new_value,struct itimerspec *old_value);
		// timerid -- timer id.
		// flags -- 0, relative time; 1, absolute time
		// new_value--��ʱ�����³�ʼֵ�ͼ�����������it
		// old_value--ȡֵͨ��Ϊ0�������ĸ�������ΪNULL,����ΪNULL���򷵻ض�ʱ����ǰһ��ֵ
		
		//��һ�μ��it.it_value��ô��,�Ժ�ÿ�ζ���it.it_interval��ô��,����˵it.it_value��0��ʱ���װ��it.it_interval��ֵ
		struct itimerspec it;
		it.it_interval.tv_sec = 1;
		it.it_interval.tv_nsec = 0;
		it.it_value.tv_sec = 3;
		it.it_value.tv_nsec = 0;
	
		if (timer_settime(timerid, 0, &it, NULL) == -1)
		{
			perror("fail to timer_settime");
			exit(-1);
		}
	}
	
	
	//3. Create 3rd timer
	{
		memset(&evp, 0, sizeof(struct sigevent));
	
		evp.sigev_value.sival_int = 113;	// The timer id that developer specify. it can be passed into callback
		evp.sigev_notify = SIGEV_THREAD;	// The thread notifying way -- dispatch a new thread.
		evp.sigev_notify_function = timer_thread;	// The thread address
		
		iRet = 	timer_create(CLOCK_REALTIME, &evp, &timerid);
		printf("< timer_create(%d,..)=%d, timer id=%d >\n", CLOCK_REALTIME, iRet, *((unsigned int*)(&timerid)));
		if (iRet == -1)
		{
			perror("fail to timer_create");
			exit(-1);
		}
	
		// XXX int timer_settime(timer_t timerid, int flags, const struct itimerspec *new_value,struct itimerspec *old_value);
		// timerid -- timer id.
		// flags -- 0, relative time; 1, absolute time
		// new_value--��ʱ�����³�ʼֵ�ͼ�����������it
		// old_value--ȡֵͨ��Ϊ0�������ĸ�������ΪNULL,����ΪNULL���򷵻ض�ʱ����ǰһ��ֵ
		
		//��һ�μ��it.it_value��ô��,�Ժ�ÿ�ζ���it.it_interval��ô��,����˵it.it_value��0��ʱ���װ��it.it_interval��ֵ
		struct itimerspec it;
		it.it_interval.tv_sec = 2;
		it.it_interval.tv_nsec = 0;
		it.it_value.tv_sec = 3;
		it.it_value.tv_nsec = 0;
	
		if (timer_settime(timerid, 0, &it, NULL) == -1)
		{
			perror("fail to timer_settime");
			exit(-1);
		}
	}

	pause();

	return 0;
}
/*
 * int timer_gettime(timer_t timerid, struct itimerspec *curr_value);
 * ��ȡtimeridָ���Ķ�ʱ����ֵ������curr_value
 *
 */