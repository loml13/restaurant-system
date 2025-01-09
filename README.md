《餐厅点餐结算系统设计》项目要求
一、餐厅点餐结算系统基本要求
1、 本系统用户包括消费者、收银员、厨师、服务员、餐厅老板、系统管理员等。

2、 消费者现场点餐并分配餐位，并得到小票，可以预订餐位。

3、 收银员负责对小票进行结算并收费，当消费金额不足500元时需要收取餐位费，结算时，只能对“已出菜”菜品进行结算，收银员还需要对当天的结算进行统计，当天结束后，还需要统计当天“待做”菜品和“已做”菜品。

4、 厨师可以按序查看每个小票并做菜，当做完一个菜时需要更改该菜的状态（菜的初始状态均为“待做”，已出菜的菜品应改为“已做”），厨师也可以查看当天已完成的所有菜品。

5、 服务员可以查看小票并将已进行服务，也可以根据客户的要求增加菜肴或加点酒水，增加的菜肴或加点的酒水由服务员录入该客户的小票中，已端到餐桌的菜其状态需要改为“已出菜”。

6、 餐厅老板可以对所有信息进行查看，以及进行各种统计查询。

7、 系统管理员对系统基本数据进行管理，包括餐位、菜肴、酒水等基础数据。

二、餐厅点餐结算系统的使用说明
1、 配置CMakeLists.txt文件，将其中的数据库连接信息修改为自己的数据库连接信息。

2、 使用CLion打开项目，配置好CMakeLists.txt文件后，编译运行项目

3、用户名和用户密码可自行在user文件修改，orders和menu文件同上