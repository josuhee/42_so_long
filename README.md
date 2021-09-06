<hr/>  
<h3 align="center">🌱 42_so_long 🌱</h3>  
<hr/>  


### 🔎 Mandatory
- map을 파싱하고 opengl을 활용하여 그릴 것.
	- 1 : wall
	- C : collectible
	- E : exit
	- P : player
- 플레이어가 움직인 발걸음 수를 쉘에 표시할 것.
- C(collectible)을 전부 획득해야 맵을 탈출할 수 있음.  
<br/>  

🌟 **게임 화면** 🌟  
![ezgif com-gif-maker](https://user-images.githubusercontent.com/69746967/132163906-8923774b-ea15-4173-a069-cc4c11ae2357.gif)  
  
<br/>  

### 🔎 Bonus
- enemy patrols that cause the player to lose in case of contact.
- There's some sprite animation.
- Movement count is directly displayed on the screen instead of shell output.  

<br/>  


🌟 **게임 화면 : Game Clear** 🌟  
![ezgif com-gif-maker (1)](https://user-images.githubusercontent.com/69746967/132163950-7c5d8f1d-167c-4206-98e1-f2b3d83cb597.gif)  

🌟 **게임 화면 : Game Over** 🌟  
![ezgif com-gif-maker (2)](https://user-images.githubusercontent.com/69746967/132164004-eea1d72b-b2da-4269-9ad9-5a9c9bba8591.gif)  
  
<br/>  


### 🔎 수정 & 개선해야할 사항
- Mandatory 부분, 맵 파싱 과정에서 A(enemy)에 대한 예외처리를 하지 않음.
- Bonus 부분, A(enemy)가 P(player)를 찾아가는 최단 알고리즘에서 연산횟수를 줄일 필요가 있음. 또한, 적이 플레이어를 찾아가는 알고리즘에서 E(exit) 혹은 C(collectible)을 1(wall)로 인식하여 길을 돌아가게 됨.
- 엔딩크래딧이 있으면 좋겠다.


