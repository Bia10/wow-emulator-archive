-- phpMyAdmin SQL Dump
-- version 2.6.0-pl3
-- http://www.phpmyadmin.net
-- 
-- M�quina: localhost
-- Data de Cria��o: 14-Jan-2005 �s 00:42
-- Vers�o do servidor: 3.23.52
-- vers�o do PHP: 4.3.4
-- 
-- Base de Dados: `wowd`
-- 

-- --------------------------------------------------------

-- 
-- Estrutura da tabela `npc_gossip`
-- 

DROP TABLE IF EXISTS `npc_gossip`;
CREATE TABLE IF NOT EXISTS `npc_gossip` (
  `ID` int(11) NOT NULL default '0',
  `NPC_GUID` int(11) NOT NULL default '0',
  `GOSSIP_TYPE` int(11) NOT NULL default '0',
  `TEXTID` int(30) NOT NULL default '0',
  `OPTION_COUNT` int(30) default NULL,
  PRIMARY KEY  (`ID`,`NPC_GUID`)
) TYPE=MyISAM;

-- 
-- Extraindo dados da tabela `npc_gossip`
-- 

INSERT INTO `npc_gossip` VALUES (1, 9, 1, 1, 1);