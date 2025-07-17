<template>
  <div class="min-h-screen bg-gradient-to-br from-slate-900 to-slate-800">
    <!-- Barra de navegación -->
    <nav class="bg-slate-800/90 backdrop-blur-sm border-b border-slate-700 sticky top-0 z-50">
      <div class="container mx-auto px-6 py-4">
        <div class="flex items-center justify-between">
          <h1 class="text-2xl font-bold bg-gradient-to-r from-blue-400 to-purple-400 bg-clip-text text-transparent">
            Visor OBJ 3D
          </h1>
          
          <div class="flex space-x-1">
            <router-link
              v-for="route in routes"
              :key="route.path"
              :to="route.path"
              class="px-4 py-2 rounded-lg text-sm font-medium transition-all duration-200"
              :class="isActiveRoute(route.path) 
                ? 'bg-blue-600 text-white shadow-lg' 
                : 'text-slate-300 hover:text-white hover:bg-slate-700'"
            >
              {{ route.name }}
            </router-link>
          </div>
        </div>
      </div>
    </nav>

    <!-- Contenido principal -->
    <main class="container mx-auto px-6 py-8">
      <router-view />
    </main>
  </div>
</template>

<script setup>
import { computed } from 'vue'
import { useRoute } from 'vue-router'

const route = useRoute()

const routes = [
  { path: '/introduccion', name: 'Introducción' },
  { path: '/visualizador', name: 'Visualizador' },
  { path: '/modelo1', name: 'Modelo 1' },
  { path: '/modelo2', name: 'Modelo 2' }
]

const isActiveRoute = (path) => {
  return route.path === path
}
</script>
