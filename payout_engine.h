#ifndef PAYOUT_ENGINE_H
# define PAYOUT_ENGINE_H

#define TRANS_MAX 66
#define ADDR_MAX 35

struct btc_trans
{
	char trans_hash[TRANS_MAX];
	char from_addr[ADDR_MAX];
	char to_addr[ADDR_MAX];
	/*long int satoshi;*/
	char satoshi[TRANS_MAX];
};

#endif /* PAYOUT_ENGINE_H */
