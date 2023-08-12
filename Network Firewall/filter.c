#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>

MODULE_LICENSE( "GPL" );

static struct nf_hook_ops *nfho = NULL;
static char *ips[10] = {};
module_param_array(ips, charp, NULL, 0);
MODULE_PARM_DESC(ips, "An array of ip addresses");

/* Hook function */
static unsigned int hook_func(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {
    struct iphdr *ip_header;
    struct tcphdr *tcp_header;
    struct udphdr *udp_header;

    /* Get the IP header */
    ip_header = ip_hdr(skb);

    /* Check if the packet is TCP or UDP */
    if (ip_header->protocol == IPPROTO_TCP) {
        /* Get the TCP header */
        tcp_header = (struct tcphdr *)((__u32 *)ip_header + ip_header->ihl);

        /* Print the source and destination IP addresses and ports */
        printk(KERN_INFO "Outgoing TCP packet: %pI4:%d -> %pI4:%d\n",
            &ip_header->saddr, ntohs(tcp_header->source),
            &ip_header->daddr, ntohs(tcp_header->dest));
    } else if (ip_header->protocol == IPPROTO_UDP) {
        /* Get the UDP header */
        udp_header = (struct udphdr *)((__u32 *)ip_header + ip_header->ihl);

        /* Print the source and destination IP addresses and ports */
        printk(KERN_INFO "Outgoing UDP packet: %pI4:%d -> %pI4:%d\n",
            &ip_header->saddr, ntohs(udp_header->source),
            &ip_header->daddr, ntohs(udp_header->dest));
    }

    return NF_ACCEPT;
}

//static char *ip_addr_rule = "95.217.163.246";
static char *ip_addr_rule2 = "1.1.1.1";

#define IPADDRESS(addr) \
	((unsigned char *)&addr)[3], \
	((unsigned char *)&addr)[2], \
	((unsigned char *)&addr)[1], \
	((unsigned char *)&addr)[0]

static unsigned int nf_blockicmppkt_handler(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
	struct iphdr *iph;  
	struct udphdr *udph; 
	if(!skb)
		return NF_ACCEPT;
	iph = ip_hdr(skb); // retrieve the IP headers from the packet
	char *str = (char *)kmalloc(16, GFP_KERNEL);
	u32 sip;	
	sip = ntohl(iph->saddr);	
	sprintf(str, "%u.%u.%u.%u", IPADDRESS(sip)); 
	
	for (i = 0; i < ARRAY_SIZE(ips); i++){
		if(ips[i]==null)
			continue;
		static char *ip_addr_rule = ips[i];
		if(iph->protocol == IPPROTO_UDP) {
			if(strcmp(str, ip_addr_rule)==0 || strcmp(str, ip_addr_rule2)==0){
				return NF_ACCEPT;
			} else {
				return NF_DROP;	
			} 
			udph = udp_hdr(skb);
			if(ntohs(udph->dest) == 53) {
				return NF_ACCEPT; 
			}
		}
		else if (iph->protocol == IPPROTO_TCP) {
			if(strcmp(str, ip_addr_rule)==0){
				return NF_ACCEPT;
			} else {
				return NF_DROP;	
			}
		}
		else if (iph->protocol == IPPROTO_ICMP) {
			if(strcmp(str, ip_addr_rule)==0){
				return NF_ACCEPT;
			} else {
				return NF_DROP;	
			}
		}
		return NF_ACCEPT;
	}
}

static struct nf_hook_ops *nf_blockicmppkt_ops = NULL;

/* Initialize the module */
static int __init init_module_func(void) {
    nfho = (struct nf_hook_ops*)kcalloc(1, sizeof(struct nf_hook_ops), GFP_KERNEL);
    if(nfho !=NULL) {

	nfho->hook = (nf_hookfn*)hook_func;
    	nfho->hooknum = NF_INET_LOCAL_OUT;
    	nfho->pf = PF_INET;
    	nfho->priority = NF_IP_PRI_FIRST;
    }
    nf_register_net_hook(&init_net, nfho);
    
    nf_blockicmppkt_ops = (struct nf_hook_ops*)kcalloc(1,  sizeof(struct nf_hook_ops),GFP_KERNEL);
	if (nf_blockicmppkt_ops != NULL) {
		nf_blockicmppkt_ops->hook = (nf_hookfn*)nf_blockicmppkt_handler;
		nf_blockicmppkt_ops->hooknum = NF_INET_PRE_ROUTING;
		nf_blockicmppkt_ops->pf = NFPROTO_IPV4;
		nf_blockicmppkt_ops->priority = NF_IP_PRI_FIRST; // set the priority
		
		nf_register_net_hook(&init_net, nf_blockicmppkt_ops);
	}

    printk(KERN_INFO "Module loaded\n");
    return 0;
}

/* Cleanup the module */
static void __exit cleanup_module_func(void) {
    nf_unregister_net_hook(&init_net, nfho);
    nf_unregister_net_hook(&init_net, nf_blockicmppkt_ops);

    printk(KERN_INFO "Module unloaded\n");
}

/* Define the module */
module_init(init_module_func);
module_exit(cleanup_module_func);
