import { createApp } from "vue"
import { createRouter, createWebHistory } from "vue-router"
import App from "./App.vue"
import Introduccion from "./components/Introduccion.vue"
import Visualizador from "./components/Visualizador.vue"
import Modelo1 from "./components/Modelo1.vue"
import Modelo2 from "./components/Modelo2.vue"

const routes = [
  { path: "/", redirect: "/introduccion" },
  { path: "/introduccion", component: Introduccion },
  { path: "/visualizador", component: Visualizador },
  { path: "/modelo1", component: Modelo1 },
  { path: "/modelo2", component: Modelo2 },
]

const router = createRouter({
  history: createWebHistory(),
  routes,
})

const app = createApp(App)
app.use(router)
app.mount("#app")
