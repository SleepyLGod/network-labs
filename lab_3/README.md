# 3rd: CPT-based Networking Lab

⭐ using [Cisco Packet Tracer](https://skillsforall.com/resources/lab-downloads) simulation software to complete the content

## 🍃 Tasks

### 🌈 1st: IP address planning and VLan assignment experiment

Use simulation software to describe network topology

**Basic content 1**
- Set PC1 and PC2 in the same network segment, the subnet address is: 192.168.0.0/24;
- Set PC3~PC8 in the same network segment, the subnet address is: 192.168.1.0/24;
- Configure the router so that the PCs in the two subnets can communicate freely.

**Basic content 2**
- Set PC1 and PC2 in the same network segment, the subnet address is: 192.168.0.0/24;
- Set PC3, PC5, and PC7 in the same network segment, and the subnet address is: 192.168.1.0/24;
- Set PC4, PC6 and PC8 in the same network segment, the subnet address is: 192.168.2.0/24;
- Configure switches 1, 2, 3, and 4 so that PC1 and PC2 belong to Vlan2, PC3, PC5, and PC7 belong to Vlan3, and PC4, PC6, and PC8 belong to Vlan4;
- Test the connectivity between PCs and analyze them in combination with the theoretical knowledge you have learned;
- Configure the router so that the PCs on the topology map can communicate freely, and describe your router configuration process in detail in combination with the theory you have learned.

### 🌈 2nd:  routing configuration experiment

Use simulation software to describe network topology

**Basic content 1**
- Set PC1 to the network segment of 192.168.1.0/24;
- Set PC2 to the network segment of 192.168.2.0/24;
- Set PC3 to the network segment of 192.168.3.0/24;
- Set PC4 to 192.168.4.0/24 network segment
- Set the IP address of the router port
- Configure the RIP protocol on the router so that each PC can access each other

**Basic content 2** 
- Set PC1 to the network segment of 192.168.1.0/24;
- Set PC2 to the network segment of 192.168.2.0/24;
- Set PC3 to the network segment of 192.168.3.0/24;
- Set PC4 to 192.168.4.0/24 network segment
- Set the IP address of the router port
- Configure the OSPF protocol on the router so that each PC can access each other

**Basic content 3**
- On the basis of basic content 1 or 2, perform access control configuration on router A, so that PC1 cannot access other PCs, nor can it be accessed by other PCs.
- On the basis of basic content 1 or 2, perform access control configuration on router A, so that PC1 cannot access PC2, but can access other PCs

### 🥇 3rd:  Comprehensive part

**Experimental background:**

  A school has applied for an address block with a prefix of 211.69.4.0/22, planning to connect the entire school to the network. The school has 4 colleges, 1 library, 3 student dormitories. Each college has 20 hosts, the library has 100 hosts, and each dormitory has 200 hosts.
Networking requirements:

- The library can access the Internet wirelessly
- Colleges can visit each other
- Student dormitories can visit each other
- The college and the student dormitory cannot visit each other
- The library is accessible from both the Faculty and the halls of residence.

**Experimental task requirements:**
- Complete the design of the network topology and draw it on the simulation software (requires sufficient but minimal equipment, no need to consider equipment redundancy backup
The problem)
- According to the content of the theoretical class, reasonably allocate the IP addresses of the whole network
- Configure various devices on the drawn network topology diagram, and test whether they meet the networking requirements. If there is something that cannot be met, please give an explanation and explanation based on the theory
