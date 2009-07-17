#include <stdio.h>
#include <openssl/evp.h>
#include <string.h>

unsigned hamdist(unsigned x, unsigned y);
unsigned numbits(unsigned v);
int hash_hamdist(unsigned char* x, unsigned char* y, int hash_len, unsigned int max);

main(int argc, char *argv[])
{
	EVP_MD_CTX mdctx;
	const EVP_MD *md;

	// The challenge phrase we want to match
	char ch_phrase[] = "I am not a big believer in fortune telling";
	unsigned char ch_hash[EVP_MAX_MD_SIZE];

	char mess1[] = "Rubinius one eight six active active record memcached exception JRuby DHH TOKYO";
	unsigned char md_value[EVP_MAX_MD_SIZE];
	int md_len, i;

	md = EVP_sha1();

	if(!md) {
		printf("Error creating SHA-1 message digest\n");
		exit(1);
	}

	EVP_MD_CTX_init(&mdctx);

	// Hash the challenge phrase
	EVP_DigestInit_ex(&mdctx, md, NULL);
	EVP_DigestUpdate(&mdctx, ch_phrase, strlen(ch_phrase));
	EVP_DigestFinal_ex(&mdctx, ch_hash, &md_len);

	printf("Challenge phrase hash is: ");
	for(i = 0; i < md_len; i++)
	{
		printf("%02x", ch_hash[i]);
	}
	printf("\n");


	// Make a copy of the message and padd it for the 5 trailing characters
	int messLength = strlen(mess1);
	char altMess1[messLength + 6]; // 1 space, 5 chars, 1 null

	strncpy(altMess1, mess1, messLength);
	altMess1[messLength] = ' ';

	for (i = (messLength + 1); i <= (messLength + 5); i++)
	{
		altMess1[i] = '!';
	}
	altMess1[messLength + 6] = '\0';


	unsigned int mindist = 1000;
	unsigned int dist;
	int j, k, l, m, n;
	int charPos1 = messLength + 1;
	int charPos2 = messLength + 2;
	int charPos3 = messLength + 3;
	int charPos4 = messLength + 4;
	int charPos5 = messLength + 5;
	int altMessLength = strlen(altMess1);

	for (i = 33; i < 126; i++)
	{
		altMess1[charPos1] = i;
//DEBUG		printf("messLength: %i, altMess1: %s\n", messLength, altMess1);
		for (j = 33; j < 126; j++)
		{
			altMess1[charPos2] = j;

			for (k = 33; k < 126; k++)
			{
				altMess1[charPos3] = k;

				for (l = 33; l < 126; l++)
				{
					altMess1[charPos4] = l;

					for (m = 33; m < 126; m++)
					{
						altMess1[charPos5] = m;

						// Hash mess1
						EVP_DigestInit_ex(&mdctx, md, NULL);
						EVP_DigestUpdate(&mdctx, altMess1, altMessLength);
						EVP_DigestFinal_ex(&mdctx, md_value, &md_len);

						EVP_MD_CTX_cleanup(&mdctx);

						dist = hash_hamdist(ch_hash, md_value, md_len, mindist);

						if (dist != -1)
						{
							mindist = dist;

							printf("Lower distance found (%u).\nMessage: %s Hash: ", dist, altMess1);
							for(n = 0; n < md_len; n++)
								printf("%02x", md_value[n]);
							printf("\n");
						}
					}
				}
			}
		}
	}

	printf("Lowest Hamming Distance: %i\n", mindist);
}

int hash_hamdist(unsigned char* x, unsigned char* y, int hash_len, unsigned int max)
{
	unsigned int dist = 0; 
	int i;
	for(i = 0; i < hash_len; i++)
	{
		dist += hamdist(x[i], y[i]);
		if (dist >= max)
		{
			return -1;
		}
	}

	return dist;
}

unsigned hamdist(unsigned x, unsigned y)
{
	return numbits(x ^ y);
}

unsigned numbits(unsigned v)
{
	unsigned int c;
	for (c = 0; v; c++)
	{
		v &= v - 1; // clear the least significant bit set
	}

	return c;
}

